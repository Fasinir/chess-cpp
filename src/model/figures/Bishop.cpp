#include "Bishop.h"

#include "../move/VisionUtil.h"

Bishop::Bishop(const ChessColor &color) : Figure(color) {
    this->move_types_ = std::vector{MoveType::kBishop};
}

char Bishop::getSymbol() const {
    return this->color_ == ChessColor::kWhite ? 'B' : 'b';
}

std::unique_ptr<Figure> Bishop::clone() const {
    return std::make_unique<Bishop>(*this);
}

std::string Bishop::getName() const {
    return "bishop";
}

std::vector<Coordinates> Bishop::getVision(const ChessBoard &board, const Coordinates &from) const {
    std::vector<Coordinates> v;
    VisionUtil::rayVision(board, from, 1, 1, v);
    VisionUtil::rayVision(board, from, 1, -1, v);
    VisionUtil::rayVision(board, from, -1, -1, v);
    VisionUtil::rayVision(board, from, -1, 1, v);
    return v;
}
