#include "ApplyMoveResult.h"

#include <utility>

ApplyMoveResult::ApplyMoveResult(const Move &move) : move_(move) {
    this->taken_figure_ = std::nullopt;
}

ApplyMoveResult::ApplyMoveResult(const Move &move, std::shared_ptr<Figure> taken_figure) : move_(move),
    taken_figure_(std::move(taken_figure)) {
}

ApplyMoveResult::ApplyMoveResult(const Move &move,
                                 std::optional<std::shared_ptr<Figure> > taken_figure) : move_(move),
    taken_figure_(std::move(taken_figure)) {
}

Move ApplyMoveResult::getMove() const {
    return move_;
}

std::optional<std::shared_ptr<Figure> > ApplyMoveResult::getTakenFigure() const {
    return taken_figure_;
}
