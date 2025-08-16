#include "Queen.h"

#include "../move/VisionUtil.h"

Queen::Queen(ChessColor color) : Figure(color) {
}

char Queen::getSymbol() const {
    return this->color_ == ChessColor::kWhite ? 'Q' : 'q';
}

std::unique_ptr<Figure> Queen::clone() const {
    return std::make_unique<Queen>(*this);
}

std::string Queen::getName() const {
    return "queen";
}

std::vector<Coordinates> Queen::getVision(std::shared_ptr<ChessBoard> board, const Coordinates &from) const {
    std::vector<Coordinates> v;
    // rook rays
    VisionUtil::rayVision(board, from,  1,  0, v);
    VisionUtil::rayVision(board, from, -1,  0, v);
    VisionUtil::rayVision(board, from,  0,  1, v);
    VisionUtil::rayVision(board, from,  0, -1, v);
    // bishop rays
    VisionUtil::rayVision(board, from,  1,  1, v);
    VisionUtil::rayVision(board, from,  1, -1, v);
    VisionUtil::rayVision(board, from, -1, -1, v);
    VisionUtil::rayVision(board, from, -1,  1, v);
    return v;
}
