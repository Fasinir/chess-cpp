#ifndef FIGURE_H
#define FIGURE_H
#include <memory>
#include <iostream>

#include "../../Constants.h"


class Figure {
protected:
    Constants::Color color;

public:
    explicit Figure(const Constants::Color color) : color(color) {
    };

    virtual ~Figure() = default;

    [[nodiscard]] virtual char getSymbol() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Figure> clone() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Figure &figure);
};


#endif //FIGURE_H
