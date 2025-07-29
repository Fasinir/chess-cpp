#include "ChessController.h"

#include "../model/board/move/Coordinates.h"
#include "../model/board/subscribers/KingPositionSubscriber.h"
#include <QMessageBox>
#include <iostream>

ChessController::ChessController(QObject *parent)
    : QObject(parent),
      board(ChessBoard::STANDARD_BOARD()),
      moveApplier(std::make_unique<MoveApplier>()), settings(), manager(std::make_unique<MoveSubscriptionManager>()) {
    std::shared_ptr<EnPassantSubscriber> enPassantSubscriber = std::make_shared<EnPassantSubscriber>();
    std::shared_ptr<CastleSubscriber> castleChecker = std::make_shared<CastleSubscriber>();
    std::shared_ptr<KingPositionSubscriber> kingPositionSubscriber = std::make_shared<KingPositionSubscriber>();

    this->moveGetter = std::make_unique<LegalMoveGetter>(enPassantSubscriber, castleChecker,
                                                         std::make_shared<MoveApplier>(),
                                                         kingPositionSubscriber);
    manager->addSubscription(castleChecker);
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
    ChessColor color = whiteToMove ? ChessColor::WHITE : ChessColor::BLACK;
    currentLegalMoves = moveGetter->getLegalMovesForColor(*board, color);

    std::cout << (whiteToMove ? "White" : "Black") << "'s turn. Legal moves: "
            << currentLegalMoves.size() << "\n";

    if (currentLegalMoves.empty()) {
        auto kingPosSub = std::make_shared<KingPositionSubscriber>(); // If not injected elsewhere
        Coordinates kingPos = kingPosSub->getKingCoordinates(color);

        bool inCheck = moveGetter->hasVisionOn(*board, Constants::oppositeColor(color), kingPos);

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

    moveApplier->applyMove(*board, *it);
    manager->notifySubscribers(*it);
    emit boardUpdated();

    whiteToMove = !whiteToMove;
    nextTurn();
}
