#ifndef BISHOP_H
#define BISHOP_H
#include "Figure.h"


class Bishop : public Figure {
public:
    explicit Bishop(Constants::Color color): Figure(color) {
    }

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;
};


#endif //BISHOP_H
