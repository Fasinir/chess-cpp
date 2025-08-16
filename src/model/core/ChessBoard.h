#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Field.h"
#include "../../Constants.h"
#include <optional>

#include "../figures/Figure.h"

class ChessBoard {
    std::array<std::array<Field, Constants::kBoardSize>, Constants::kBoardSize> board_;

public:
    ChessBoard() = default;

    ~ChessBoard() = default;

    static std::unique_ptr<ChessBoard> makeStandardBoard();

    std::optional<std::shared_ptr<Figure> > placeFigure(const std::shared_ptr<Figure> &figure, const Coordinates &coordinates);

    [[nodiscard]] std::optional<std::shared_ptr<Figure> > figureAt(const Coordinates &coordinates) const;

    void removeFigure(const Coordinates &coordinates);

    friend std::ostream &operator<<(std::ostream &os, const ChessBoard &board);

    [[nodiscard]] std::string toFENBoardPart() const;
};


#endif //BOARD_H
