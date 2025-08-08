#include "ApplyMoveResult.h"

#include <utility>

ApplyMoveResult::ApplyMoveResult(const Move &move) : move_(move) {
    this->taken_figure_ = std::nullopt;
}

ApplyMoveResult::ApplyMoveResult(const Move &move, std::shared_ptr<Figure> takenFigure) : move_(move),
    taken_figure_(std::move(takenFigure)) {
}

ApplyMoveResult::ApplyMoveResult(const Move &move,
                                 std::optional<std::shared_ptr<Figure> > takenFigure) : move_(move),
    taken_figure_(std::move(takenFigure)) {
}

Move ApplyMoveResult::getMove() const {
    return move_;
}

std::optional<std::shared_ptr<Figure> > ApplyMoveResult::getTakenFigure() const {
    return taken_figure_;
}
