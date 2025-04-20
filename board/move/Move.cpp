#include "Move.h"

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << move.from << "->" << move.to << "(" << move.type << ")";
    return os;
}

Coordinates Move::getFrom() const {
    return from;
}

Coordinates Move::getTo() const {
    return to;
}

MoveType Move::getType() const {
    return type;
}
