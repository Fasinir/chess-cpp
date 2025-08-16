#include "Knight.h"
#include "../../Constants.h"

Knight::Knight(const ChessColor &color) : Figure(color) {
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

std::vector<Coordinates> Knight::getVision(std::shared_ptr<ChessBoard> board, const Coordinates &from) const {
    static constexpr int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    static constexpr int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    std::vector<Coordinates> v;
    for (int i = 0; i < 8; ++i) {
        int x = from.getX() + dx[i];
        int y = from.getY() + dy[i];
        if (Constants::InBounds(x, y))
            v.emplace_back(x, y);
    }
    return v;
}
