#include "VisionBoard.h"

VisionBoard::VisionBoard(const std::vector<Move> &moves) : board_() {
    for (auto move: moves) {
        board_[move.getTo().getX()][move.getTo().getY()] = true;
    }
}

bool VisionBoard::attacks(const Coordinates &coordinates) const {
    return board_.at(coordinates.getX()).at(coordinates.getY());
}
