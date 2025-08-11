#ifndef PAWN_H
#define PAWN_H
#include "Figure.h"


class Pawn final : public Figure {
public:
    explicit Pawn(ChessColor color);

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;

    [[nodiscard]] std::string getName() const override;

    std::vector<Coordinates> getVision(const ChessBoard &board, const Coordinates &from) const override;
};


#endif //PAWN_H
