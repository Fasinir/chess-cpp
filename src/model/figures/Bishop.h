#ifndef BISHOP_H
#define BISHOP_H
#include "Figure.h"
#include "../core/ChessColor.h"


class Bishop final : public Figure {
public:
    explicit Bishop(const ChessColor &color);

    [[nodiscard]] char getSymbol() const override;

    [[nodiscard]] std::unique_ptr<Figure> clone() const override;

    [[nodiscard]] std::string getName() const override;

    std::vector<Coordinates> getVision(std::shared_ptr<ChessBoard> board, const Coordinates &from) const override;
};


#endif //BISHOP_H
