#ifndef QUEEN_H
#define QUEEN_H
#include "Figure.h"


class Queen final : public Figure {
public:
    explicit Queen(ChessColor color);

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;

    [[nodiscard]] std::string getName() const override;
};


#endif //QUEEN_H
