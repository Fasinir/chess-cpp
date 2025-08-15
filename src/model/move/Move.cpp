#include "Move.h"

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << move.from_ << "->" << move.to_ << "(" << move.tag_ << ")";
    return os;
}

Coordinates Move::getFrom() const {
    return from_;
}

Coordinates Move::getTo() const {
    return to_;
}

std::string Move::getTag() const {
    return tag_;
}
