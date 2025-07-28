#include "Queen.h"

Queen::Queen(ChessColor color) : Figure(color) {
    this->moves = std::vector{
        MoveType::ROOK, MoveType::BISHOP
    };
}

char Queen::getSymbol() const {
    return this->color == ChessColor::WHITE ? 'Q' : 'q';
}

std::unique_ptr<Figure> Queen::clone() const {
    return std::make_unique<Queen>(*this);
}

std::string Queen::getName() const {
    return "queen";
}
