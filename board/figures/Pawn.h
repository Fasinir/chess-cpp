#ifndef PAWN_H
#define PAWN_H
#include "Figure.h"


class Pawn : public Figure {
public:
    explicit Pawn(Constants::Color color): Figure(color) {
    }

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;
};


#endif //PAWN_H
