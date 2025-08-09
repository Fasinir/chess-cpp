#include "PawnPositionSubscriber.h"

#include <utility>

PawnPositionSubscriber::PawnPositionSubscriber(std::shared_ptr<EnPassantSubscriber> enPassantSubscriber) {
    this->en_passant_subscriber_ = std::move(enPassantSubscriber);
    this->pawn_positions_ = std::unordered_set<Coordinates>();
    for (int i = 0; i < Constants::kBoardSize; i++) {
        pawn_positions_.insert(Coordinates(i, 1));
        pawn_positions_.insert(Coordinates(i, 6));
    }
}

void PawnPositionSubscriber::notify(const ApplyMoveResult &applyMoveResult) {
    Move move = applyMoveResult.getMove();
    if (pawn_positions_.contains(move.getTo())) {
        pawn_positions_.erase(move.getTo());
        std::cout << "Pawn was taken regularly" << std::endl;
    }
    if (pawn_positions_.contains(move.getFrom())) {
        pawn_positions_.erase(move.getFrom());
        // if no promotion update the position
        if (move.getTo().getY() != 0 && move.getTo().getY() != 7) {
            pawn_positions_.insert(move.getTo());
            std::cout << "Regular move" << std::endl;
        } else {
            std::cout << "Pawn was promoted" << std::endl;
        }
        if (en_passant_subscriber_->canBeTakenEnPassant(move.getTo())) {
            int takenEnPassantYCoordinate = move.getTo().getY() == 2 ? 3 : 4;
            pawn_positions_.erase(Coordinates(move.getTo().getX(), takenEnPassantYCoordinate));
            std::cout << "Pawn was taken en passant" << std::endl;
        }
    }
    std::cout << pawn_positions_.size() << std::endl;
}

std::unordered_set<Coordinates> PawnPositionSubscriber::getPawnPositions() {
    return pawn_positions_;
}
