#include "VisionUtil.h"

void VisionUtil::rayVision(const ChessBoard &board, const Coordinates &from, int dx, int dy,
                           std::vector<Coordinates> &out) {
    int x = from.getX() + dx;
    int y = from.getY() + dy;
    while (x >= 0 && y >= 0 && x < Constants::kBoardSize && y < Constants::kBoardSize) {
        out.emplace_back(x, y);
        if (board.figureAt(x, y).has_value()) break; // blocked
        x += dx;
        y += dy;
    }
}
