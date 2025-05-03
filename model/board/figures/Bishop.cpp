#include "Bishop.h"

Bishop::Bishop(ChessColor color) : Figure(color) {
    this->moves = std::vector{MoveType::BISHOP};
}

char Bishop::getSymbol() const {
    return this->color == ChessColor::WHITE ? 'B' : 'b';
}

std::unique_ptr<Figure> Bishop::clone() const {
    return std::make_unique<Bishop>(*this);
}
