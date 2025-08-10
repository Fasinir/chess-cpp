#ifndef MOVECONDITION_H
#define MOVECONDITION_H
#include <ostream>

enum class MoveType {
    kPawnDoubleMove, kPawnSingleMove, kEnPassant, kPawnTaking,
    kKnight,
    kBishop,
    kRook,
    kKing, kCastle
};

std::ostream &operator<<(std::ostream &os, MoveType move_type);
#endif //MOVECONDITION_H
