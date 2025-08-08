#include "Move.h"

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << move.from_ << "->" << move.to_ << "(" << move.type_ << ")";
    return os;
}

Coordinates Move::getFrom() const {
    return from_;
}

Coordinates Move::getTo() const {
    return to_;
}

MoveType Move::getType() const {
    return type_;
}
