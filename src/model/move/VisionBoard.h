#ifndef VISIONBOARD_H
#define VISIONBOARD_H
#include <array>

#include "Coordinates.h"
#include "Move.h"
#include "../core/Constants.h"

class VisionBoard {
    std::array<std::array<bool, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> board;

public:
    VisionBoard() = default;
    explicit VisionBoard(const std::vector<Move>& moves);
    ~VisionBoard() = default;

    [[nodiscard]] bool hasVisionOn(Coordinates coordinates) const;
};


#endif //VISIONBOARD_H
