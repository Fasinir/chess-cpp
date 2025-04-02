#ifndef ROOK_H
#define ROOK_H
#include "Figure.h"


class Rook : public Figure {
public:
    explicit Rook(Constants::Color color): Figure(color) {
    }

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;
};


#endif //ROOK_H
