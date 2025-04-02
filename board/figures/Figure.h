#ifndef FIGURE_H
#define FIGURE_H
#include "../../Constants.h"


class Figure {
    Constants::Color color;

public:
    explicit Figure(const Constants::Color color) : color(color) {
    };

    virtual char getSymbol() const = 0;

    virtual ~Figure() = default;
};


#endif //FIGURE_H
