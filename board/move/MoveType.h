#ifndef MOVECONDITION_H
#define MOVECONDITION_H
#include <ostream>


enum class MoveType {
    PAWN_DOUBLE_MOVE, PAWN_SINGLE_MOVE, EN_PASSANT, PAWN_TAKING,
    KNIGHT,
    DIAGONAL,
    VERTICAL, HORIZONTAL,
    KING, CASTLE
};

std::ostream& operator<<(std::ostream& os, MoveType moveType);
#endif //MOVECONDITION_H
