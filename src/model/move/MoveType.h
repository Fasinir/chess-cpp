#ifndef MOVECONDITION_H
#define MOVECONDITION_H
#include <ostream>

enum class MoveType {
    PAWN_DOUBLE_MOVE, PAWN_SINGLE_MOVE, EN_PASSANT, PAWN_TAKING,
    KNIGHT,
    BISHOP,
    ROOK,
    KING, CASTLE
};

std::ostream &operator<<(std::ostream &os, MoveType move_type);
#endif //MOVECONDITION_H
