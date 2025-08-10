#include "Queen.h"

Queen::Queen(ChessColor color) : Figure(color) {
    this->move_types_ = std::vector{
        MoveType::kRook, MoveType::kBishop
    };
}

char Queen::getSymbol() const {
    return this->color_ == ChessColor::kWhite ? 'Q' : 'q';
}

std::unique_ptr<Figure> Queen::clone() const {
    return std::make_unique<Queen>(*this);
}

std::string Queen::getName() const {
    return "queen";
}
