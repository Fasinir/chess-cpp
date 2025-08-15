#include "EnPassantSubscriber.h"

EnPassantSubscriber::EnPassantSubscriber() {
    this->en_passant_coordinates_;
    this->unmoved_pawns_;
    for (int i = 0; i < 8; i++) {
        unmoved_pawns_.insert(Coordinates(i, 1));
        unmoved_pawns_.insert(Coordinates(i, 6));
    }
}

bool EnPassantSubscriber::canBeTakenEnPassant(const Coordinates kCoordinates) const {
    if (this->en_passant_coordinates_.has_value()) {
        return kCoordinates == this->en_passant_coordinates_;
    }
    return false;
}

void EnPassantSubscriber::setEnPassantCoordinates(Coordinates coordinates) {
    this->en_passant_coordinates_ = coordinates;
}

void EnPassantSubscriber::notify(const ApplyMoveResult &apply_move_result) {
    en_passant_coordinates_.reset();
    std::shared_ptr move = apply_move_result.getMove();
    if (unmoved_pawns_.contains(move->getFrom())) {
        unmoved_pawns_.erase(move->getFrom());
        if (std::abs(move->getTo().getY() - move->getFrom().getY()) == 2) {
            const int kEnPassantYCoordinate = move->getFrom().getY() == 1 ? 2 : 5;
            setEnPassantCoordinates(Coordinates(move->getFrom().getX(), kEnPassantYCoordinate));
            std::cout << "En Passant is possible for: " << Coordinates(move->getFrom().getX(), kEnPassantYCoordinate) <<
                    std::endl;
        }
    }
    if (unmoved_pawns_.contains(move->getTo())) {
        unmoved_pawns_.erase(move->getTo());
    }
}
