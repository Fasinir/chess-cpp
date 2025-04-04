#ifndef MOVE_H
#define MOVE_H
#include "Coordinates.h"
#include "MoveType.h"


class Move {
    Coordinates from;
    Coordinates to;
    MoveType type;

public:
    Move(const Coordinates from, const Coordinates to, const MoveType type) : from(from), to(to), type(type) {
    };

    ~Move() = default;

    friend std::ostream &operator<<(std::ostream &os, const Move &move);

    [[nodiscard]] Coordinates getFrom() const;

    [[nodiscard]] Coordinates getTo() const;

    [[nodiscard]] MoveType getType() const;
};


#endif //MOVE_H
