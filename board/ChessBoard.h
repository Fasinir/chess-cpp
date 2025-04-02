#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Field.h"
#include "../Constants.h"
#include <iostream>

#include "figures/Figure.h"

class ChessBoard {
    std::array<std::array<Field, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> board;

public:
    ChessBoard() = default;

    ~ChessBoard() = default;

    static std::unique_ptr<ChessBoard> STANDARD_BOARD();

    void placeFigure(std::unique_ptr<Figure> figure, int row, int col);

    friend std::ostream &operator<<(std::ostream &os, const ChessBoard &board);
};


#endif //BOARD_H
