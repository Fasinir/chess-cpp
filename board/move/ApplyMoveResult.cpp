#include "ApplyMoveResult.h"

#include <utility>

ApplyMoveResult::ApplyMoveResult(const Move &move) : move(move) {
    this->takenFigure = std::nullopt;
}

ApplyMoveResult::ApplyMoveResult(const Move &move, std::shared_ptr<Figure> takenFigure) : move(move),
    takenFigure(std::move(takenFigure)) {
}

ApplyMoveResult::ApplyMoveResult(const Move &move,
                                 std::optional<std::shared_ptr<Figure> > takenFigure) : move(move),
    takenFigure(std::move(takenFigure)) {
}

Move ApplyMoveResult::getMove() const {
    return move;
}

std::optional<std::shared_ptr<Figure> > ApplyMoveResult::getTakenFigure() const {
    return takenFigure;
}
