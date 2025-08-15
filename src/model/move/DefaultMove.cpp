#include "DefaultMove.h"

#include "ApplyMoveResult.h"

ApplyMoveResult DefaultMove::apply(std::shared_ptr<ChessBoard> board) {
    std::shared_ptr<Figure> optional_from_figure = board->figureAt(from_.getX(), from_.getY()).value();
    board->removeFigure(from_.getX(), from_.getY());
    const std::shared_ptr<Figure> &from_figure = optional_from_figure;
    std::optional<std::shared_ptr<Figure> > optional_to_figure = board->placeFigure(
        from_figure,
        to_.getX(), to_.getY());
    return ApplyMoveResult(std::const_pointer_cast<Move>(shared_from_this()), optional_to_figure);
}

void DefaultMove::undo(std::shared_ptr<ChessBoard> board, std::optional<std::shared_ptr<Figure> > optional_taken_figure) {
    auto to_fig = board->figureAt(to_.getX(), to_.getY()).value();
    board->placeFigure(to_fig, from_.getX(), from_.getY());

    if (optional_taken_figure.has_value()) {
        board->placeFigure(optional_taken_figure.value(), to_.getX(), to_.getY());
    } else {
        board->removeFigure(to_.getX(), to_.getY());
    }
}
