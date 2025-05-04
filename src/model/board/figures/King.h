#ifndef KING_H
#define KING_H
#include "Figure.h"


class King : public Figure {
public:
    explicit King(ChessColor color);

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;
};


#endif //KING_H
