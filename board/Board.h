#ifndef BOARD_H
#define BOARD_H

#include <array>

#include "Field.h"


class Board {
    std::array<std::array<Figure, 8>, 8> board;

public:
    Board();

    ~ Board() = default;
};


#endif //BOARD_H
