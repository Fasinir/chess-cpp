#include "MoveType.h"

std::ostream& operator<<(std::ostream& os, MoveType moveType) {
    switch (moveType) {
        case MoveType::PAWN_DOUBLE_MOVE: os << "Pawn Double Move"; break;
        case MoveType::PAWN_SINGLE_MOVE: os << "Pawn Single Move"; break;
        case MoveType::EN_PASSANT: os << "En Passant"; break;
        case MoveType::PAWN_TAKING: os << "Pawn Taking"; break;
        case MoveType::KNIGHT: os << "Knight"; break;
        case MoveType::BISHOP: os << "Diagonal"; break;
        case MoveType::ROOK: os << "Straight"; break;
        case MoveType::KING: os << "King"; break;
        case MoveType::CASTLE: os << "Castle"; break;
        default: os << "Unknown MoveType"; break;
    }
    return os;
}
