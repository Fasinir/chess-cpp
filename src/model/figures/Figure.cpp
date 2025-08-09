#include "Figure.h"

std::ostream &operator<<(std::ostream &os, const Figure &figure) {
    os << figure.getSymbol();
    return os;
}

std::vector<MoveType> &Figure::getMoveTypes() {
    return move_types_;
}

const ChessColor &Figure::getColor() const {
    return color_;
}
