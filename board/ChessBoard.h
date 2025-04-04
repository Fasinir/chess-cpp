#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Field.h"
#include "../Constants.h"
#include <iostream>
#include <optional>

#include "figures/Figure.h"

class ChessBoard {
    std::array<std::array<Field, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> board;

public:
    ChessBoard() = default;

    ~ChessBoard() = default;

    static std::unique_ptr<ChessBoard> STANDARD_BOARD();

    /**
     *
     * @param figure figure to be placed
     * @param row
     * @param col
     * @return optional of pointer to figure that was previously at these coordinates
     */
    std::optional<std::shared_ptr<Figure> > placeFigure(const std::shared_ptr<Figure>& figure, int row, int col);

    [[nodiscard]] std::optional<std::shared_ptr<Figure> > figureAt(int row, int col) const;

    void removeFigure(int row, int col);

    friend std::ostream &operator<<(std::ostream &os, const ChessBoard &board);
};


#endif //BOARD_H
