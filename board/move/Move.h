#ifndef MOVE_H
#define MOVE_H
#include "Coordinates.h"


class Move {
    Coordinates from;
    Coordinates to;

public:
    Move(const Coordinates from, const Coordinates to) : from(from), to(to) {
    };

    ~Move() = default;

    friend std::ostream &operator<<(std::ostream &os, const Move &move);
};


#endif //MOVE_H
