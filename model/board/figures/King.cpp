#include "King.h"

King::King(ChessColor color) : Figure(color) {
    this->moves = std::vector{MoveType::KING, MoveType::CASTLE};
}

char King::getSymbol() const {
    return this->color == ChessColor::WHITE ? 'K' : 'k';
}

std::unique_ptr<Figure> King::clone() const {
    return std::make_unique<King>(*this);
}
