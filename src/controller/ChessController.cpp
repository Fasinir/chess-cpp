#include "ChessController.h"

#include "../model/board/move/Coordinates.h"
#include "../model/board/subscribers/move_subs/KingPositionSubscriber.h"
#include <QMessageBox>
#include <iostream>

#include "../model/board/figures/Bishop.h"
#include "../model/board/figures/Knight.h"
#include "../model/board/figures/Queen.h"
#include "../model/board/figures/Rook.h"
#include "../model/board/subscribers/move_subs/FiftyMoveSubscriber.h"
#include "../model/board/subscribers/move_subs/PawnPositionSubscriber.h"

ChessController::ChessController(QObject *parent)
    : QObject(parent),
      board(ChessBoard::STANDARD_BOARD()),
      moveApplier(std::make_unique<MoveApplier>()), kingPositionSubscriber(std::make_shared<KingPositionSubscriber>()),
      settings(),
      manager(std::make_unique<MoveSubscriptionManager>()),
      threefoldBoardSubscriber(std::make_unique<ThreefoldBoardSubscriber>()),
      castleSubscriber(std::make_unique<CastleSubscriber>()),
      enPassantSubscriber(std::make_shared<EnPassantSubscriber>()) {
    this->moveGetter = std::make_unique<LegalMoveGetter>(enPassantSubscriber, castleSubscriber,
                                                         std::make_shared<MoveApplier>(),
                                                         kingPositionSubscriber);
    std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber = std::make_shared<PawnPositionSubscriber>(
        enPassantSubscriber);
    this->fiftyMoveSubscriber = std::make_shared<FiftyMoveSubscriber>(pawnPositionSubscriber);
    this->promotionSubscriber = std::make_shared<PromotionSubscriber>(pawnPositionSubscriber);
    manager->addSubscription(castleSubscriber);
    manager->addSubscription(kingPositionSubscriber);
    manager->addSubscription(fiftyMoveSubscriber);
    manager->addSubscription(promotionSubscriber);
    manager->addSubscription(pawnPositionSubscriber);
    manager->addSubscription(enPassantSubscriber);
}

void ChessController::startGame(const GameSettings &settings) {
    this->settings = settings;
    this->whiteToMove = true;

    std::cout << "Game started\n";
    std::cout << "White: " << settings.whitePlayerName.toStdString() << "\n";
    std::cout << "Black: " << settings.blackPlayerName.toStdString() << "\n";

    nextTurn();
}

void ChessController::nextTurn() {
    if (threefoldBoardSubscriber->updateAndCheckIfThreefoldWasReached(*board, *castleSubscriber, *enPassantSubscriber,
                                                                      whiteToMove)) {
        QMessageBox::information(nullptr, "Game Over", "Draw by threefold repetition");
    }
    if (fiftyMoveSubscriber->fiftyMoveRuleIsReached()) {
        QMessageBox::information(nullptr, "Game Over", "Draw by 50 move rule");
    }
    if (promotionSubscriber->getPromotionCoordinates().has_value()) {
        Coordinates promotionCoordinates = promotionSubscriber->getPromotionCoordinates().value();
        ChessColor color = board->figureAt(promotionCoordinates.getX(), promotionCoordinates.getY()).value()->
                getColor();
        promotionSubscriber->resetPromotionCoordinates();
        emit promotionRequested(promotionCoordinates, color);
        return; // Pause the game until promotion is handled
    }
    ChessColor color = whiteToMove ? ChessColor::WHITE : ChessColor::BLACK;
    currentLegalMoves = moveGetter->getLegalMovesForColor(*board, color);

    std::cout << (whiteToMove ? "White" : "Black") << "'s turn. Legal moves: "
            << currentLegalMoves.size() << "\n";

    if (currentLegalMoves.empty()) {
        Coordinates kingPos = kingPositionSubscriber->getKingCoordinates(color);
        std::shared_ptr visionBoard = std::make_shared<VisionBoard>(
            moveGetter->getLegalMovesForColor(*board, Constants::oppositeColor(color)));
        bool inCheck = visionBoard->hasVisionOn(kingPos);

        QString resultText;
        if (inCheck)
            resultText = whiteToMove ? "Checkmate! Black wins." : "Checkmate! White wins.";
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


    auto it = std::find_if(currentLegalMoves.begin(), currentLegalMoves.end(), [&](const Move &move) {
        return move.getFrom() == from && move.getTo() == to;
    });

    if (it == currentLegalMoves.end()) {
        std::cout << "Illegal move attempted.\n";
        emit illegalMoveAttempted();
        return;
    }

    std::cout << "Move accepted: " << *it << "\n";

    auto applyMoveResult = moveApplier->applyMove(*board, *it);
    manager->notifySubscribers(*applyMoveResult);
    emit boardUpdated();

    whiteToMove = !whiteToMove;
    nextTurn();
}

void ChessController::promote(Coordinates coordinates, PromotionType type) {
    std::shared_ptr<Figure> promoted;

    switch (type) {
        case PromotionType::QUEEN:
            promoted = std::make_shared<Queen>(
                board->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
        case PromotionType::ROOK:
            promoted = std::make_shared<Rook>(
                board->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
        case PromotionType::BISHOP:
            promoted = std::make_shared<Bishop>(
                board->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
        case PromotionType::KNIGHT:
            promoted = std::make_shared<Knight>(
                board->figureAt(coordinates.getX(), coordinates.getY()).value()->getColor());
            break;
    }
    board->removeFigure(coordinates.getX(), coordinates.getY());
    board->placeFigure(promoted, coordinates.getX(), coordinates.getY());

    emit boardUpdated();

    nextTurn();
}
