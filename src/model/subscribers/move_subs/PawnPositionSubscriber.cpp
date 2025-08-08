#include "PawnPositionSubscriber.h"

#include <utility>

PawnPositionSubscriber::PawnPositionSubscriber(std::shared_ptr<EnPassantSubscriber> enPassantSubscriber) {
    this->enPassantSubscriber = std::move(enPassantSubscriber);
    this->pawnPositions = std::unordered_set<Coordinates>();
    for (int i = 0; i < Constants::kBoardSize; i++) {
        pawnPositions.insert(Coordinates(i, 1));
        pawnPositions.insert(Coordinates(i, 6));
    }
}

void PawnPositionSubscriber::notify(const ApplyMoveResult &applyMoveResult) {
    Move move = applyMoveResult.getMove();
    if (pawnPositions.contains(move.getTo())) {
        pawnPositions.erase(move.getTo());
        std::cout << "Pawn was taken regularly" << std::endl;
    }
    if (pawnPositions.contains(move.getFrom())) {
        pawnPositions.erase(move.getFrom());
        // if no promotion update the position
        if (move.getTo().getY() != 0 && move.getTo().getY() != 7) {
            pawnPositions.insert(move.getTo());
            std::cout << "Regular move" << std::endl;
        } else {
            std::cout << "Pawn was promoted" << std::endl;
        }
        if (enPassantSubscriber->canBeTakenEnPassant(move.getTo())) {
            int takenEnPassantYCoordinate = move.getTo().getY() == 2 ? 3 : 4;
            pawnPositions.erase(Coordinates(move.getTo().getX(), takenEnPassantYCoordinate));
            std::cout << "Pawn was taken en passant" << std::endl;
        }
    }
    std::cout << pawnPositions.size() << std::endl;
}

std::unordered_set<Coordinates> PawnPositionSubscriber::getPawnPositions() {
    return pawnPositions;
}
