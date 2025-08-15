#include "King.h"
#include "../core/Constants.h"

King::King(const ChessColor &color) : Figure(color) {
    this->move_types_ = std::vector{MoveType::kKing, MoveType::kCastle};
}

char King::getSymbol() const {
    return this->color_ == ChessColor::kWhite ? 'K' : 'k';
}

std::unique_ptr<Figure> King::clone() const {
    return std::make_unique<King>(*this);
}

std::string King::getName() const {
    return "king";
}

std::vector<Coordinates> King::getVision(std::shared_ptr<ChessBoard> board, const Coordinates &from) const {
    static constexpr int dx[8] = {1, 1, 1, 0, -1, -1, -1, 0};
    static constexpr int dy[8] = {1, 0, -1, -1, -1, 0, 1, 1};
    std::vector<Coordinates> v;
    for (int i = 0; i < 8; ++i) {
        int x = from.getX() + dx[i];
        int y = from.getY() + dy[i];
        if (x >= 0 && y >= 0 && x < Constants::kBoardSize && y < Constants::kBoardSize)
            v.emplace_back(x, y);
    }
    return v;
}
