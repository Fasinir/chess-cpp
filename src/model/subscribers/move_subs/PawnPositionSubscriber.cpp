#include "PawnPositionSubscriber.h"

#include <utility>
#include "../../core/Constants.h"

PawnPositionSubscriber::PawnPositionSubscriber(std::shared_ptr<EnPassantSubscriber> en_passant_subscriber) {
    this->en_passant_subscriber_ = std::move(en_passant_subscriber);
    this->pawn_positions_ = std::unordered_set<Coordinates>();
    for (int i = 0; i < Constants::kBoardSize; i++) {
        pawn_positions_.insert(Coordinates(i, 1));
        pawn_positions_.insert(Coordinates(i, 6));
    }
}

void PawnPositionSubscriber::notify(const ApplyMoveResult &apply_move_result) {
    std::shared_ptr move = apply_move_result.getMove();
    if (pawn_positions_.contains(move->getTo())) {
        pawn_positions_.erase(move->getTo());
        std::cout << "Pawn was taken regularly" << std::endl;
    }
    if (pawn_positions_.contains(move->getFrom())) {
        pawn_positions_.erase(move->getFrom());
        // if no promotion update the position
        if (move->getTo().getY() != 0 && move->getTo().getY() != 7) {
            pawn_positions_.insert(move->getTo());
            std::cout << "Regular move" << std::endl;
        } else {
            std::cout << "Pawn was promoted" << std::endl;
        }
        if (en_passant_subscriber_->canBeTakenEnPassant(move->getTo())) {
            int taken_en_passant_y_coordinate = move->getTo().getY() == 2 ? 3 : 4;
            pawn_positions_.erase(Coordinates(move->getTo().getX(), taken_en_passant_y_coordinate));
            std::cout << "Pawn was taken en passant" << std::endl;
        }
    }
    std::cout << pawn_positions_.size() << std::endl;
}

std::unordered_set<Coordinates> PawnPositionSubscriber::getPawnPositions() {
    return pawn_positions_;
}
