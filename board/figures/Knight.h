#ifndef KNIGHT_H
#define KNIGHT_H
#include "Figure.h"


class Knight : public Figure {
public:
    explicit Knight(ChessColor color);

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;
};


#endif //KNIGHT_H
