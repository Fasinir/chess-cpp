#include "Rook.h"

Rook::Rook(ChessColor color) : Figure(color) {
    this->move_types_ = std::vector{MoveType::kRook};
}

char Rook::getSymbol() const {
    return this->color_ == ChessColor::kWhite ? 'R' : 'r';
}

std::unique_ptr<Figure> Rook::clone() const {
    return std::make_unique<Rook>(*this);
}

std::string Rook::getName() const {
    return "rook";
}
