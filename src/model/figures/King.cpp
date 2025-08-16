#include "King.h"
#include "../../Constants.h"

King::King(const ChessColor &color) : Figure(color) {
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
        if (Constants::InBounds(x, y))
            v.emplace_back(x, y);
    }
    return v;
}
