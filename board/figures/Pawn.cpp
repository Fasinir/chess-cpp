#include "Pawn.h"

char Pawn::getSymbol() const {
    return this->color == Constants::Color::WHITE ? 'P' : 'p';
}

std::unique_ptr<Figure> Pawn::clone() const {
    return std::make_unique<Pawn>(*this);
}
