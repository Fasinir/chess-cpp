#include "Figure.h"

std::ostream &operator<<(std::ostream &os, const Figure &figure) {
    os << figure.getSymbol();
    return os;
}

const ChessColor &Figure::getColor() const {
    return color_;
}
