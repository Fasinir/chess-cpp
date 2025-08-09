#include "EnPassantSubscriber.h"

EnPassantSubscriber::EnPassantSubscriber() {
    this->en_passant_coordinates_;
    this->unmoved_pawns_;
    for (int i = 0; i < 8; i++) {
        unmoved_pawns_.insert(Coordinates(i, 1));
        unmoved_pawns_.insert(Coordinates(i, 6));
    }
}

bool EnPassantSubscriber::canBeTakenEnPassant(const Coordinates coordinates) const {
    if (this->en_passant_coordinates_.has_value()) {
        return coordinates == this->en_passant_coordinates_;
    }
    return false;
}

void EnPassantSubscriber::setEnPassantCoordinates(Coordinates coordinates) {
    this->en_passant_coordinates_ = coordinates;
}

void EnPassantSubscriber::notify(const ApplyMoveResult &applyMoveResult) {
    en_passant_coordinates_.reset();
    Move move = applyMoveResult.getMove();
    if (unmoved_pawns_.contains(move.getFrom())) {
        unmoved_pawns_.erase(move.getFrom());
        if (std::abs(move.getTo().getY() - move.getFrom().getY()) == 2) {
            const int enPassantYCoordinate = move.getFrom().getY() == 1 ? 2 : 5;
            setEnPassantCoordinates(Coordinates(move.getFrom().getX(), enPassantYCoordinate));
            std::cout << "En Passant is possible for: " << Coordinates(move.getFrom().getX(), enPassantYCoordinate) <<
                    std::endl;
        }
    }
    if (unmoved_pawns_.contains(move.getTo())) {
        unmoved_pawns_.erase(move.getTo());
    }
}
