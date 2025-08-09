#include "Bishop.h"

Bishop::Bishop(const ChessColor color) : Figure(color) {
    this->move_types_ = std::vector{MoveType::BISHOP};
}

char Bishop::getSymbol() const {
    return this->color_ == ChessColor::WHITE ? 'B' : 'b';
}

std::unique_ptr<Figure> Bishop::clone() const {
    return std::make_unique<Bishop>(*this);
}

std::string Bishop::getName() const {
    return "bishop";
}
