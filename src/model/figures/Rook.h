#ifndef ROOK_H
#define ROOK_H
#include "Figure.h"


class Rook final : public Figure {
public:
    explicit Rook(ChessColor color);

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;

    [[nodiscard]] std::string getName() const override;

    std::vector<Coordinates> getVision(const ChessBoard &board, const Coordinates &from) const override;
};


#endif //ROOK_H
