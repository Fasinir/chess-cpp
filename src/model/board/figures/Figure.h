#ifndef FIGURE_H
#define FIGURE_H
#include <memory>
#include <iostream>

#include "../../ChessColor.h"
#include "../../Constants.h"
#include "../move/MoveType.h"


class Figure {
protected:
    ChessColor color;
    std::vector<MoveType> moves;

public:
    explicit Figure(const ChessColor color) : color(color) {
    };

    virtual ~Figure() = default;

    [[nodiscard]] virtual char getSymbol() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Figure> clone() const = 0;

    [[nodiscard]] virtual std::string getName() const = 0;

    std::vector<MoveType> &getMoves();

    const ChessColor &getColor() const;

    friend std::ostream &operator<<(std::ostream &os, const Figure &figure);
};


#endif //FIGURE_H
