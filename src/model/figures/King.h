#ifndef KING_H
#define KING_H
#include "Figure.h"


class King final : public Figure {
public:
    explicit King(const ChessColor &color);

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;

    [[nodiscard]] std::string getName() const override;

    std::vector<Coordinates> getVision(const ChessBoard &board, const Coordinates &from) const override;
};


#endif //KING_H
