#include "Pawn.h"
#include "../../Constants.h"

Pawn::Pawn(ChessColor color) : Figure(color) {
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

std::vector<Coordinates> Pawn::getVision(std::shared_ptr<ChessBoard> board, const Coordinates &from) const {
    std::vector<Coordinates> v;
    int dir = (color_ == ChessColor::kWhite) ? 1 : -1;
    int y = from.getY() + dir;
    int x1 = from.getX() + 1;
    int x2 = from.getX() - 1;
    if (Constants::InBounds(x1, y)) {
        v.emplace_back(x1, y);
    }
    if (Constants::InBounds(x2, y)) {
        v.emplace_back(x2, y);
    }
    return v;
}
