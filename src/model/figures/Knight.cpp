#include "Knight.h"

Knight::Knight(const ChessColor &color) : Figure(color) {
    this->move_types_ = std::vector{MoveType::KNIGHT};
}

char Knight::getSymbol() const {
    return this->color_ == ChessColor::WHITE ? 'N' : 'n';
}

std::unique_ptr<Figure> Knight::clone() const {
    return std::make_unique<Knight>(*this);
}

std::string Knight::getName() const {
    return "knight";
}
