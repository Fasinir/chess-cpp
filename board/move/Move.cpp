#include "Move.h"

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << move.from << "->" << move.to;
    return os;
}
