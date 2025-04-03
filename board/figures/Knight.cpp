#include "Knight.h"

Knight::Knight(ChessColor color) : Figure(color) {
    this->moves = std::vector{MoveType::KNIGHT};
}

char Knight::getSymbol() const {
    return this->color == ChessColor::WHITE ? 'K' : 'k';
}

std::unique_ptr<Figure> Knight::clone() const {
    return std::make_unique<Knight>(*this);
}
