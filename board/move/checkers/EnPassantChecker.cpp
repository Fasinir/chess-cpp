#include "EnPassantChecker.h"

bool EnPassantChecker::canBeTakenEnPassant(Coordinates coordinates) {
    if (this->enPassantCoordinates.has_value()) {
        return coordinates == this->enPassantCoordinates;
    }
    return false;
}

void EnPassantChecker::setEnPassantCoordinates(Coordinates coordinates) {
    this->enPassantCoordinates = coordinates;
}
