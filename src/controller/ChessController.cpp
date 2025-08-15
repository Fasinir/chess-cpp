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
      king_position_subscriber_(std::make_shared<KingPositionSubscriber>()),
      threefold_board_subscriber_(std::make_unique<ThreefoldBoardSubscriber>()),
      castle_subscriber_(std::make_unique<CastleSubscriber>()),
      en_passant_subscriber_(std::make_shared<EnPassantSubscriber>()),
      game_settings_(),
      move_subscription_manager_(std::make_unique<MoveSubscriptionManager>()) {
    auto pawn_position_subscriber = std::make_shared<PawnPositionSubscriber>(
        en_passant_subscriber_);
    this->move_getter_ = std::make_unique<LegalMoveGetter>(en_passant_subscriber_, castle_subscriber_,
                                                           king_position_subscriber_, pawn_position_subscriber);

    this->fifty_move_subscriber_ = std::make_shared<FiftyMoveSubscriber>(pawn_position_subscriber);
    this->pawn_promotion_subscriber_ = std::make_shared<PromotionSubscriber>(pawn_position_subscriber);
    move_subscription_manager_->addSubscriber(castle_subscriber_);
    move_subscription_manager_->addSubscriber(king_position_subscriber_);
    move_subscription_manager_->addSubscriber(fifty_move_subscriber_);
    move_subscription_manager_->addSubscriber(pawn_promotion_subscriber_);
    move_subscription_manager_->addSubscriber(pawn_position_subscriber);
    move_subscription_manager_->addSubscriber(en_passant_subscriber_);
}

void ChessController::startGame(const GameSettings &settings) {
    this->game_settings_ = settings;
    this->white_to_move_ = true;

    std::cout << "Game started\n";
    std::cout << "White: " << settings.white_player_name_.toStdString() << "\n";
    std::cout << "Black: " << settings.black_player_name_.toStdString() << "\n";

    nextTurn();
}

void ChessController::nextTurn() {
    if (threefold_board_subscriber_->updateAndCheckThreefold(*board_, *castle_subscriber_, *en_passant_subscriber_,
                                                             white_to_move_)) {
        QMessageBox::information(nullptr, "Game Over", "Draw by threefold repetition");
    }
    if (fifty_move_subscriber_->isFiftyMoveRuleReached()) {
        QMessageBox::information(nullptr, "Game Over", "Draw by 50 move rule");
    }
    if (pawn_promotion_subscriber_->getPromotionCoordinates().has_value()) {
        Coordinates promotion_coordinates = pawn_promotion_subscriber_->getPromotionCoordinates().value();
        ChessColor color = board_->figureAt(promotion_coordinates.getX(), promotion_coordinates.getY()).value()->
                getColor();
        pawn_promotion_subscriber_->resetPromotionCoordinates();
        emit promotionRequested(promotion_coordinates, color);
        return; // Pause the game until promotion is handled
    }
    ChessColor color = white_to_move_ ? ChessColor::kWhite : ChessColor::kBlack;
    current_legal_moves_ = move_getter_->getLegalMovesForColor(*board_, color);

    std::cout << (white_to_move_ ? "White" : "Black") << "'s turn. Legal moves: "
            << current_legal_moves_.size() << "\n";

    if (current_legal_moves_.empty()) {
        Coordinates king_pos = king_position_subscriber_->getKingCoordinates(color);
        std::shared_ptr vision_board = std::make_shared<VisionBoard>(
            *board_, Utils::oppositeColor(color));
        bool in_check = vision_board->attacks(king_pos);

        QString result_text;
        if (in_check)
            result_text = white_to_move_ ? "Checkmate! Black wins." : "Checkmate! White wins.";
        else
            result_text = "Stalemate!";

        std::cout << "[Game Over] " << result_text.toStdString() << "\n";
        QMessageBox::information(nullptr, "Game Over", result_text);
    }
}

std::vector<Coordinates> ChessController::legalDestinationsFrom(int col, int row) const {
    Coordinates from(col, row);
    std::vector<Coordinates> outs;
    for (const auto &m: current_legal_moves_) {
        if (m->getFrom() == from) outs.emplace_back(m->getTo());
    }
    return outs;
}

void ChessController::onPieceMoved(int from_row, int from_col, int to_row, int to_col) {
    Coordinates from(from_col, from_row);
    Coordinates to(to_col, to_row);

    std::cout << "Attempting move: (" << from.getX() << "," << from.getY()
            << ") -> (" << to.getX() << "," << to.getY() << ")\n";


    auto it = std::ranges::find_if(current_legal_moves_, [&](std::shared_ptr<Move> move) {
        return move->getFrom() == from && move->getTo() == to;
    });

    if (it == current_legal_moves_.end()) {
        std::cout << "Illegal move attempted.\n";
        emit illegalMoveAttempted();
        return;
    }

    std::cout << "Move accepted: " << *it << "\n";

    auto apply_move_result = (*it)->apply(*board_);
    move_subscription_manager_->notifySubscribers(apply_move_result);
    emit boardUpdated();

    white_to_move_ = !white_to_move_;
    nextTurn();
}

void ChessController::promote(Coordinates coordinates, PromotionType type) {
    std::shared_ptr<Figure> promoted;

    switch (type) {
        case PromotionType::kQueen:
            promoted = std::make_shared<Queen>(
                board_->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
        case PromotionType::kRook:
            promoted = std::make_shared<Rook>(
                board_->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
        case PromotionType::kBishop:
            promoted = std::make_shared<Bishop>(
                board_->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
        case PromotionType::kKnight:
            promoted = std::make_shared<Knight>(
                board_->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
    }
    board_->removeFigure(coordinates.getX(), coordinates.getY());
    board_->placeFigure(promoted, coordinates.getX(), coordinates.getY());

    emit boardUpdated();

    nextTurn();
}
