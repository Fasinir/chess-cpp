#include "Knight.h"

char Knight::getSymbol() const {
    return this->color == Constants::Color::WHITE ? 'K' : 'k';
}

std::unique_ptr<Figure> Knight::clone() const {
    return std::make_unique<Knight>(*this);
}
