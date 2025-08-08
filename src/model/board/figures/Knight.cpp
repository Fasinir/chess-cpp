#include "Knight.h"

Knight::Knight(ChessColor color) : Figure(color) {
    this->moves = std::vector{MoveType::KNIGHT};
}

char Knight::getSymbol() const {
    return this->color == ChessColor::WHITE ? 'N' : 'n';
}

std::unique_ptr<Figure> Knight::clone() const {
    return std::make_unique<Knight>(*this);
}

std::string Knight::getName() const {
    return "knight";
}
