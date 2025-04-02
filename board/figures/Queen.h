#ifndef QUEEN_H
#define QUEEN_H
#include "Figure.h"


class Queen : public Figure {
public:
    explicit Queen(Constants::Color color) : Figure(color) {
    };

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;
};


#endif //QUEEN_H
