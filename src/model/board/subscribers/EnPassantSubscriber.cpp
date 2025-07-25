#include "EnPassantSubscriber.h"

bool EnPassantSubscriber::canBeTakenEnPassant(Coordinates coordinates) {
    if (this->enPassantCoordinates.has_value()) {
        return coordinates == this->enPassantCoordinates;
    }
    return false;
}

void EnPassantSubscriber::setEnPassantCoordinates(Coordinates coordinates) {
    this->enPassantCoordinates = coordinates;
}
