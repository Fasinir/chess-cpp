#include "MoveType.h"

std::ostream& operator<<(std::ostream& os, MoveType move_type) {
    switch (move_type) {
        case MoveType::kPawnDoubleMove: os << "Pawn Double Move"; break;
        case MoveType::kPawnSingleMove: os << "Pawn Single Move"; break;
        case MoveType::kEnPassant: os << "En Passant"; break;
        case MoveType::kPawnTaking: os << "Pawn Taking"; break;
        case MoveType::kKnight: os << "Knight"; break;
        case MoveType::kBishop: os << "Diagonal"; break;
        case MoveType::kRook: os << "Straight"; break;
        case MoveType::kKing: os << "King"; break;
        case MoveType::kCastle: os << "Castle"; break;
        default: os << "Unknown MoveType"; break;
    }
    return os;
}
