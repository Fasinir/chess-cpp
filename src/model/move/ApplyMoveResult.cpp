#include "ApplyMoveResult.h"

#include <utility>

std::shared_ptr<Move> ApplyMoveResult::getMove() const {
    return move_;
}

std::optional<std::shared_ptr<Figure> > ApplyMoveResult::getTakenFigure() const {
    return taken_figure_;
}
