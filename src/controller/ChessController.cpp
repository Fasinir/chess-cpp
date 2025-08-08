#include "ChessController.h"

#include "../model/move/Coordinates.h"
#include "../model/subscribers/move_subs/KingPositionSubscriber.h"
#include <QMessageBox>
#include <iostream>

#include "../model/figures/Bishop.h"
#include "../model/figures/Knight.h"
#include "../model/figures/Queen.h"
#include "../model/figures/Rook.h"
#include "../model/subscribers/move_subs/FiftyMoveSubscriber.h"
#include "../model/subscribers/move_subs/PawnPositionSubscriber.h"

ChessController::ChessController(QObject *parent)
    : QObject(parent),
      board_(ChessBoard::makeStandardBoard()),
      move_applier_(std::make_unique<MoveApplier>()), king_position_subscriber_(std::make_shared<KingPositionSubscriber>()),
      game_settings_(),
      move_subscription_manager_(std::make_unique<MoveSubscriptionManager>()),
      threefold_board_subscriber_(std::make_unique<ThreefoldBoardSubscriber>()),
      castle_subscriber_(std::make_unique<CastleSubscriber>()),
      en_passant_subscriber_(std::make_shared<EnPassantSubscriber>()) {
    this->move_getter_ = std::make_unique<LegalMoveGetter>(en_passant_subscriber_, castle_subscriber_,
                                                         std::make_shared<MoveApplier>(),
                                                         king_position_subscriber_);
    std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber = std::make_shared<PawnPositionSubscriber>(
        en_passant_subscriber_);
    this->fifty_move_subscriber_ = std::make_shared<FiftyMoveSubscriber>(pawnPositionSubscriber);
    this->pawn_promotion_subscriber_ = std::make_shared<PromotionSubscriber>(pawnPositionSubscriber);
    move_subscription_manager_->addSubscription(castle_subscriber_);
    move_subscription_manager_->addSubscription(king_position_subscriber_);
    move_subscription_manager_->addSubscription(fifty_move_subscriber_);
    move_subscription_manager_->addSubscription(pawn_promotion_subscriber_);
    move_subscription_manager_->addSubscription(pawnPositionSubscriber);
    move_subscription_manager_->addSubscription(en_passant_subscriber_);
}

void ChessController::startGame(const GameSettings &settings) {
    this->game_settings_ = settings;
    this->white_to_move_ = true;

    std::cout << "Game started\n";
    std::cout << "White: " << settings.whitePlayerName.toStdString() << "\n";
    std::cout << "Black: " << settings.blackPlayerName.toStdString() << "\n";

    nextTurn();
}

void ChessController::nextTurn() {
    if (threefold_board_subscriber_->updateAndCheckIfThreefoldWasReached(*board_, *castle_subscriber_, *en_passant_subscriber_,
                                                                      white_to_move_)) {
        QMessageBox::information(nullptr, "Game Over", "Draw by threefold repetition");
    }
    if (fifty_move_subscriber_->fiftyMoveRuleIsReached()) {
        QMessageBox::information(nullptr, "Game Over", "Draw by 50 move rule");
    }
    if (pawn_promotion_subscriber_->getPromotionCoordinates().has_value()) {
        Coordinates promotionCoordinates = pawn_promotion_subscriber_->getPromotionCoordinates().value();
        ChessColor color = board_->figureAt(promotionCoordinates.getX(), promotionCoordinates.getY()).value()->
                getColor();
        pawn_promotion_subscriber_->resetPromotionCoordinates();
        emit promotionRequested(promotionCoordinates, color);
        return; // Pause the game until promotion is handled
    }
    ChessColor color = white_to_move_ ? ChessColor::WHITE : ChessColor::BLACK;
    current_legal_moves_ = move_getter_->getLegalMovesForColor(*board_, color);

    std::cout << (white_to_move_ ? "White" : "Black") << "'s turn. Legal moves: "
            << current_legal_moves_.size() << "\n";

    if (current_legal_moves_.empty()) {
        Coordinates kingPos = king_position_subscriber_->getKingCoordinates(color);
        std::shared_ptr visionBoard = std::make_shared<VisionBoard>(
            move_getter_->getLegalMovesForColor(*board_, Utils::oppositeColor(color)));
        bool inCheck = visionBoard->hasVisionOn(kingPos);

        QString resultText;
        if (inCheck)
            resultText = white_to_move_ ? "Checkmate! Black wins." : "Checkmate! White wins.";
        else
            resultText = "Stalemate!";

        std::cout << "[Game Over] " << resultText.toStdString() << "\n";
        QMessageBox::information(nullptr, "Game Over", resultText);
    }
}

void ChessController::onPieceMoved(int fromRow, int fromCol, int toRow, int toCol) {
    Coordinates from(fromCol, fromRow);
    Coordinates to(toCol, toRow);

    std::cout << "Attempting move: (" << from.getX() << "," << from.getY()
            << ") -> (" << to.getX() << "," << to.getY() << ")\n";


    auto it = std::find_if(current_legal_moves_.begin(), current_legal_moves_.end(), [&](const Move &move) {
        return move.getFrom() == from && move.getTo() == to;
    });

    if (it == current_legal_moves_.end()) {
        std::cout << "Illegal move attempted.\n";
        emit illegalMoveAttempted();
        return;
    }

    std::cout << "Move accepted: " << *it << "\n";

    auto applyMoveResult = move_applier_->applyMove(*board_, *it);
    move_subscription_manager_->notifySubscribers(*applyMoveResult);
    emit boardUpdated();

    white_to_move_ = !white_to_move_;
    nextTurn();
}

void ChessController::promote(Coordinates coordinates, PromotionType type) {
    std::shared_ptr<Figure> promoted;

    switch (type) {
        case PromotionType::QUEEN:
            promoted = std::make_shared<Queen>(
                board_->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
        case PromotionType::ROOK:
            promoted = std::make_shared<Rook>(
                board_->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
        case PromotionType::BISHOP:
            promoted = std::make_shared<Bishop>(
                board_->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
        case PromotionType::KNIGHT:
            promoted = std::make_shared<Knight>(
                board_->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
    }
    board_->removeFigure(coordinates.getX(), coordinates.getY());
    board_->placeFigure(promoted, coordinates.getX(), coordinates.getY());

    emit boardUpdated();

    nextTurn();
}
