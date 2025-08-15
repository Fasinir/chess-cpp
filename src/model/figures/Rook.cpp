#include "Rook.h"

#include "../move/VisionUtil.h"

Rook::Rook(ChessColor color) : Figure(color) {
    this->move_types_ = std::vector{MoveType::kRook};
}

char Rook::getSymbol() const {
    return this->color_ == ChessColor::kWhite ? 'R' : 'r';
}

std::unique_ptr<Figure> Rook::clone() const {
    return std::make_unique<Rook>(*this);
}

std::string Rook::getName() const {
    return "rook";
}

std::vector<Coordinates> Rook::getVision(std::shared_ptr<ChessBoard> board, const Coordinates &from) const {
    std::vector<Coordinates> v;
    VisionUtil::rayVision(board, from,  1,  0, v);
    VisionUtil::rayVision(board, from, -1,  0, v);
    VisionUtil::rayVision(board, from,  0,  1, v);
    VisionUtil::rayVision(board, from,  0, -1, v);
    return v;
}
