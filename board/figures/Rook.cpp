#include "Rook.h"

char Rook::getSymbol() const {
    return this->color == Constants::Color::WHITE ? 'R' : 'r';
}

std::unique_ptr<Figure> Rook::clone() const {
    return std::make_unique<Rook>(*this);
}
