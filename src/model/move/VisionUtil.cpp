#include "VisionUtil.h"

void VisionUtil::rayVision(std::shared_ptr<ChessBoard> board, const Coordinates &from, int dx, int dy,
                           std::vector<Coordinates> &out) {
    int x = from.getX() + dx;
    int y = from.getY() + dy;
    while (Constants::InBounds(x, y)) {
        out.emplace_back(x, y);
        if (board->figureAt(Coordinates(x, y)).has_value()) break;
        x += dx;
        y += dy;
    }
}
