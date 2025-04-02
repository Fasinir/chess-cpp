#include "Queen.h"

char Queen::getSymbol() const {
    return this->color == Constants::Color::WHITE ? 'Q' : 'q';
}

std::unique_ptr<Figure> Queen::clone() const {
    return std::make_unique<Queen>(*this);
}
