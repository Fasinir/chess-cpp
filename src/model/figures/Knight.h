#ifndef KNIGHT_H
#define KNIGHT_H
#include "Figure.h"


class Knight final : public Figure {
public:
    explicit Knight(const ChessColor &color);

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;

    [[nodiscard]] std::string getName() const override;
};


#endif //KNIGHT_H
