#ifndef APPLYMOVERESULT_H
#define APPLYMOVERESULT_H
#include <optional>

#include "Move.h"
#include "../figures/Figure.h"


class ApplyMoveResult {
    Move move;
    std::optional<std::shared_ptr<Figure> > takenFigure;

public:
    explicit ApplyMoveResult(const Move &move);

    ApplyMoveResult(const Move &move, std::shared_ptr<Figure> takenFigure);

    ApplyMoveResult(const Move &move, std::optional<std::shared_ptr<Figure> > takenFigure);

    [[nodiscard]] Move getMove() const;

    [[nodiscard]] std::optional<std::shared_ptr<Figure> > getTakenFigure() const;

    ~ApplyMoveResult() = default;
};


#endif //APPLYMOVERESULT_H
