#ifndef BISHOP_H
#define BISHOP_H
#include "Figure.h"
#include "../../ChessColor.h"


class Bishop : public Figure {
public:
    explicit Bishop(ChessColor color);

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;

    [[nodiscard]] std::string getName() const override;
};


#endif //BISHOP_H
