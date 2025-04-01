#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Field.h"
#include "../Constants.h"
#include <iostream>

class Board {
    std::array<std::array<Field, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> board;

public:
    Board() = default;

    ~ Board() = default;

    friend std::ostream &operator<<(std::ostream &os, const Board &board);
};


#endif //BOARD_H
