#ifndef ROOK_H
#define ROOK_H
#include "Figure.h"


class Rook : public Figure {
public:
    explicit Rook(ChessColor color);

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;

    [[nodiscard]] std::string getName() const override;
};


#endif //ROOK_H
