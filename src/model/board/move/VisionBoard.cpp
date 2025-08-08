#include "VisionBoard.h"

VisionBoard::VisionBoard(const std::vector<Move> &moves) : board() {
    for (auto move: moves) {
        board[move.getTo().getX()][move.getTo().getY()] = true;
    }
}

bool VisionBoard::hasVisionOn(Coordinates coordinates) const {
    return board.at(coordinates.getX()).at(coordinates.getY());
}
