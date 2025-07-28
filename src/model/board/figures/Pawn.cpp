#include "Pawn.h"


Pawn::Pawn(ChessColor color) : Figure(color) {
    this->moves = std::vector{
        MoveType::PAWN_TAKING, MoveType::PAWN_SINGLE_MOVE, MoveType::PAWN_DOUBLE_MOVE, MoveType::EN_PASSANT
    };
}

char Pawn::getSymbol() const {
    return this->color == ChessColor::WHITE ? 'P' : 'p';
}

std::unique_ptr<Figure> Pawn::clone() const {
    return std::make_unique<Pawn>(*this);
}

std::string Pawn::getName() const {
    return "pawn";
}
