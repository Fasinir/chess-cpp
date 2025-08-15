#ifndef FIGURE_H
#define FIGURE_H
#include <memory>
#include <iostream>

#include "../core/ChessColor.h"
#include "../move/MoveType.h"
#include "../move/Coordinates.h"

class ChessBoard;

class Figure {
protected:
    ChessColor color_;
    std::vector<MoveType> move_types_;

public:
    explicit Figure(const ChessColor &color) : color_(color) {
    }

    virtual ~Figure() = default;

    [[nodiscard]] virtual char getSymbol() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Figure> clone() const = 0;

    [[nodiscard]] virtual std::string getName() const = 0;

    std::vector<MoveType> &getMoveTypes();

    [[nodiscard]] const ChessColor &getColor() const;

    virtual std::vector<Coordinates> getVision(std::shared_ptr<ChessBoard> board, const Coordinates &from) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Figure &figure);
};


#endif //FIGURE_H
