#include "Coordinates.h"

std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates) {
    os << "[" << coordinates.x << ", " << coordinates.y << "]";
    return os;
}

int Coordinates::getX() const {
    return x;
}

int Coordinates::getY() const {
    return y;
}
