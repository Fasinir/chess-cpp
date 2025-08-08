#ifndef VISIONBOARD_H
#define VISIONBOARD_H
#include <array>

#include "Coordinates.h"
#include "Move.h"
#include "../core/Constants.h"

class VisionBoard {
    std::array<std::array<bool, Constants::kBoardSize>, Constants::kBoardSize> board;

public:
    VisionBoard() = default;
    explicit VisionBoard(const std::vector<Move>& moves);
    ~VisionBoard() = default;

    [[nodiscard]] bool hasVisionOn(Coordinates coordinates) const;
};


#endif //VISIONBOARD_H
