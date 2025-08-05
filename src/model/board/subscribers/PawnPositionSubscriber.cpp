#include "PawnPositionSubscriber.h"

#include <utility>

PawnPositionSubscriber::PawnPositionSubscriber(std::shared_ptr<EnPassantSubscriber> enPassantSubscriber) {
    this->enPassantSubscriber = std::move(enPassantSubscriber);
    this->pawnPositions = std::unordered_set<Coordinates>();
    for (int i = 0; i < 8; i++) {
        pawnPositions.insert(Coordinates(i, 1));
        pawnPositions.insert(Coordinates(i, 6));
    }
}

void PawnPositionSubscriber::notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) {
    Move move = applyMoveResult.getMove();
    std::cout << "Checking if these coordinates can be taken enPassant: " << move.getTo() << std::endl;
    if (pawnPositions.contains(move.getFrom()) &&
        enPassantSubscriber->canBeTakenEnPassant(move.getTo())) {
        pawnPositions.erase(move.getFrom());
        pawnPositions.insert(move.getTo());
        // white pawn was taken en passant
        int takenEnPassantYCoordinate = move.getTo().getY() == 2 ? 3 : 4;
        pawnPositions.erase(Coordinates(move.getTo().getX(), takenEnPassantYCoordinate));
        std::cout << "Pawn was taken en passant" << std::endl;
    } else if (pawnPositions.contains(move.getFrom())) {
        pawnPositions.erase(move.getFrom());
        pawnPositions.insert(move.getTo());
        std::cout << "Regular move" << std::endl;
    }
    else if (pawnPositions.contains(move.getTo())) {
        pawnPositions.erase(move.getTo());
        std::cout << "Pawn was taken regularly" << std::endl;
    }
    if (move.getTo().getY() == 0 && move.getFrom().getY() == 7) {
        pawnPositions.erase(move.getFrom());
        std::cout << "Pawn was promoted" << std::endl;
    }
    std::cout << pawnPositions.size() << std::endl;
}

std::unordered_set<Coordinates> PawnPositionSubscriber::getPawnPositions() {
    return pawnPositions;
}
