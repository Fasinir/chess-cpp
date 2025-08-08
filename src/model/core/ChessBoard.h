#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Field.h"
#include "Constants.h"
#include <optional>

#include "../figures/Figure.h"

class ChessBoard {
    std::array<std::array<Field, Constants::BOARD_SIZE>, Constants::BOARD_SIZE> board;

public:
    ChessBoard() = default;

    ~ChessBoard() = default;

    static std::unique_ptr<ChessBoard> STANDARD_BOARD();

    /**
     *
     * @param figure figure to be placed
     * @param x
     * @param y
     * @return optional of pointer to figure that was previously at these coordinates
     */
    std::optional<std::shared_ptr<Figure> > placeFigure(const std::shared_ptr<Figure>& figure, int x, int y);

    [[nodiscard]] std::optional<std::shared_ptr<Figure> > figureAt(int x, int y) const;

    void removeFigure(int x, int y);

    friend std::ostream &operator<<(std::ostream &os, const ChessBoard &board);

    [[nodiscard]] std::string toFENBoardPart() const;
};


#endif //BOARD_H
