#include "Pawn.h"


Pawn::Pawn(ChessColor color) : Figure(color) {
    this->move_types_ = std::vector{
        MoveType::kPawnTaking, MoveType::kPawnSingleMove, MoveType::kPawnDoubleMove, MoveType::kEnPassant
    };
}

char Pawn::getSymbol() const {
    return this->color_ == ChessColor::kWhite ? 'P' : 'p';
}

std::unique_ptr<Figure> Pawn::clone() const {
    return std::make_unique<Pawn>(*this);
}

std::string Pawn::getName() const {
    return "pawn";
}
