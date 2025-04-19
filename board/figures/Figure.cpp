#include "Figure.h"


std::ostream &operator<<(std::ostream &os, const Figure &figure) {
    os << figure.getSymbol();
    return os;
}

std::vector<MoveType> &Figure::getMoves() {
    return moves;
}

const ChessColor &Figure::getColor() const {
    return color;
}
