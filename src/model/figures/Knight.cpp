#include "Knight.h"
#include "../core/Constants.h"

Knight::Knight(const ChessColor &color) : Figure(color) {
    this->move_types_ = std::vector{MoveType::kKnight};
}

char Knight::getSymbol() const {
    return this->color_ == ChessColor::kWhite ? 'N' : 'n';
}

std::unique_ptr<Figure> Knight::clone() const {
    return std::make_unique<Knight>(*this);
}

std::string Knight::getName() const {
    return "knight";
}

std::vector<Coordinates> Knight::getVision(const ChessBoard &, const Coordinates &from) const {
    static constexpr int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    static constexpr int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    std::vector<Coordinates> v;
    for (int i = 0; i < 8; ++i) {
        int x = from.getX() + dx[i];
        int y = from.getY() + dy[i];
        if (x >= 0 && y >= 0 && x < Constants::kBoardSize && y < Constants::kBoardSize)
            v.emplace_back(x, y);
    }
    return v;
}
