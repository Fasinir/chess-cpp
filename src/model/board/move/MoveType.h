#ifndef MOVECONDITION_H
#define MOVECONDITION_H
#include <ostream>

// TODO: convert to class maybe?
enum class MoveType {
    PAWN_DOUBLE_MOVE, PAWN_SINGLE_MOVE, EN_PASSANT, PAWN_TAKING,
    KNIGHT,
    BISHOP,
    ROOK,
    KING, CASTLE
};

std::ostream &operator<<(std::ostream &os, MoveType moveType);
#endif //MOVECONDITION_H
