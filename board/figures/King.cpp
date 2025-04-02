#include "King.h"

char King::getSymbol() const {
    return this->color == Constants::Color::WHITE ? 'K' : 'k';
}

std::unique_ptr<Figure> King::clone() const {
    return std::make_unique<King>(*this);
}
