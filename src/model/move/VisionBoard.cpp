#include "VisionBoard.h"

VisionBoard::VisionBoard(const std::vector<Move> &moves) {
    for (auto move: moves) {
        board_[move.getTo().getX()][move.getTo().getY()] = true;
    }
}

VisionBoard::VisionBoard(const ChessBoard &board, ChessColor color) {
    for (int x = 0; x < Constants::kBoardSize; ++x) {
        for (int y = 0; y < Constants::kBoardSize; ++y) {
            auto f = board.figureAt(x, y);
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
