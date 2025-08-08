#include "Rook.h"

Rook::Rook(ChessColor color) : Figure(color) {
    this->moves = std::vector{MoveType::ROOK};
}

char Rook::getSymbol() const {
    return this->color == ChessColor::WHITE ? 'R' : 'r';
}

std::unique_ptr<Figure> Rook::clone() const {
    return std::make_unique<Rook>(*this);
}

std::string Rook::getName() const {
    return "rook";
}
