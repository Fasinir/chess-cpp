#include "VisionBoard.h"

VisionBoard::VisionBoard(std::shared_ptr<ChessBoard> board, ChessColor color) {
    for (int x = 0; x < Constants::kBoardSize; ++x) {
        for (int y = 0; y < Constants::kBoardSize; ++y) {
            auto f = board->figureAt(Coordinates(x, y));
            if (!f.has_value()) continue;
            if (f.value()->getColor() != color) continue;
            for (auto c: f.value()->getVision(board, Coordinates(x, y))) {
                this->board_[c.getX()][c.getY()] = true;
            }
        }
    }
}

bool VisionBoard::attacks(const Coordinates &coordinates) const {
    return board_.at(coordinates.getX()).at(coordinates.getY());
}
