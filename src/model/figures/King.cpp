#include "King.h"

King::King(const ChessColor kColor) : Figure(kColor) {
    this->move_types_ = std::vector{MoveType::kKing, MoveType::kCastle};
}

char King::getSymbol() const {
    return this->color_ == ChessColor::kWhite ? 'K' : 'k';
}

std::unique_ptr<Figure> King::clone() const {
    return std::make_unique<King>(*this);
}

std::string King::getName() const {
    return "king";
}
