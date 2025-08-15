#ifndef VISIONBOARD_H
#define VISIONBOARD_H
#include <array>

#include "Coordinates.h"
#include "Move.h"
#include "../core/Constants.h"
#include  "../core/ChessBoard.h"

class VisionBoard {
    std::array<std::array<bool, Constants::kBoardSize>, Constants::kBoardSize> board_{};

public:
    VisionBoard() = default;

    VisionBoard(const ChessBoard &board, ChessColor color);

    bool attacks(const Coordinates &coordinates) const;
};


#endif //VISIONBOARD_H
