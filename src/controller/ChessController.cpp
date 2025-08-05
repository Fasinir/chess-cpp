#include "ChessController.h"

#include "../model/board/move/Coordinates.h"
#include "../model/board/subscribers/KingPositionSubscriber.h"
#include <QMessageBox>
#include <iostream>

#include "../model/board/subscribers/FiftyMoveSubscriber.h"
#include "../model/board/subscribers/PawnPositionSubscriber.h"

ChessController::ChessController(QObject *parent)
    : QObject(parent),
      board(ChessBoard::STANDARD_BOARD()),
      moveApplier(std::make_unique<MoveApplier>()), kingPositionSubscriber(std::make_shared<KingPositionSubscriber>()),
      settings(),
      manager(std::make_unique<MoveSubscriptionManager>()) {
    std::shared_ptr<EnPassantSubscriber> enPassantSubscriber = std::make_shared<EnPassantSubscriber>();
    std::shared_ptr<CastleSubscriber> castleChecker = std::make_shared<CastleSubscriber>();

    this->moveGetter = std::make_unique<LegalMoveGetter>(enPassantSubscriber, castleChecker,
                                                         std::make_shared<MoveApplier>(),
                                                         kingPositionSubscriber);
    std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber = std::make_shared<PawnPositionSubscriber>(
        enPassantSubscriber);
    this->fiftyMoveSubscriber = std::make_shared<FiftyMoveSubscriber>(pawnPositionSubscriber);
    manager->addSubscription(castleChecker);
    manager->addSubscription(kingPositionSubscriber);
    manager->addSubscription(fiftyMoveSubscriber);
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
    if (fiftyMoveSubscriber->fiftyMoveRuleIsReached()) {
        QMessageBox::information(nullptr, "Game Over", "Draw by 50 move rule");
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
    manager->notifySubscribers(*applyMoveResult, *board);
    emit boardUpdated();

    whiteToMove = !whiteToMove;
    nextTurn();
}
