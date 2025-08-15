#ifndef APPLYMOVERESULT_H
#define APPLYMOVERESULT_H
#include <optional>

#include "Move.h"
#include "../figures/Figure.h"


class ApplyMoveResult {
    std::shared_ptr<Move> move_;
    std::optional<std::shared_ptr<Figure> > taken_figure_;

public:
    explicit ApplyMoveResult(std::shared_ptr<Move> move,
                             std::optional<std::shared_ptr<Figure>> taken = std::nullopt)
        : move_(std::move(move)), taken_figure_(std::move(taken)) {}

    [[nodiscard]] std::shared_ptr<Move> getMove() const;

    [[nodiscard]] std::optional<std::shared_ptr<Figure> > getTakenFigure() const;

    ~ApplyMoveResult() = default;
};


#endif //APPLYMOVERESULT_H
