#include "Coordinates.h"

std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates) {
    os << "[" << coordinates.x << ", " << coordinates.y << "]";
    return os;
}
