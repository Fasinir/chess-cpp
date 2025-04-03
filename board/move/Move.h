#ifndef MOVE_H
#define MOVE_H
#include "Coordinates.h"
#include "MoveType.h"


class Move {
    Coordinates from;
    Coordinates to;
    MoveType type;

public:
    Move(const Coordinates from, const Coordinates to, MoveType type) : from(from), to(to), type(type) {
    };

    ~Move() = default;

    friend std::ostream &operator<<(std::ostream &os, const Move &move);
};


#endif //MOVE_H
