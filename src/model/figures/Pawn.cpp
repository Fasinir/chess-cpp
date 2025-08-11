#include "Pawn.h"
#include "../core/Constants.h"

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

std::vector<Coordinates> Pawn::getVision(const ChessBoard &, const Coordinates &from) const {
    std::vector<Coordinates> v;
    int dir = (color_ == ChessColor::kWhite) ? 1 : -1;
    int y = from.getY() + dir;
    int x1 = from.getX() + 1;
    int x2 = from.getX() - 1;
    if (y >= 0 && y < Constants::kBoardSize) {
        if (x1 >= 0 && x1 < Constants::kBoardSize) v.emplace_back(x1, y);
        if (x2 >= 0 && x2 < Constants::kBoardSize) v.emplace_back(x2, y);
    }
    return v;
}
