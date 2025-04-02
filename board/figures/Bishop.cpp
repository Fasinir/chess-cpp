#include "Bishop.h"

char Bishop::getSymbol() const {
    return this->color == Constants::Color::WHITE ? 'B' : 'b';
}

std::unique_ptr<Figure> Bishop::clone() const {
    return std::make_unique<Bishop>(*this);
}
