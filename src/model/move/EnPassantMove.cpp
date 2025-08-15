#include "EnPassantMove.h"
#include "ApplyMoveResult.h"

ApplyMoveResult EnPassantMove::apply(std::shared_ptr<ChessBoard> board) {
    auto pawn = board->figureAt(from_.getX(), from_.getY()).value();
    board->placeFigure(pawn, to_.getX(), to_.getY());
    board->removeFigure(from_.getX(), from_.getY());

    int taken_x = to_.getX();
    int taken_y = (to_.getY() == 2) ? (to_.getY() + 1) : (to_.getY() - 1);
    auto taken = board->figureAt(taken_x, taken_y);
    board->removeFigure(taken_x, taken_y);

    return ApplyMoveResult(std::const_pointer_cast<Move>(shared_from_this()), taken);
}

void EnPassantMove::undo(std::shared_ptr<ChessBoard> board, std::optional<std::shared_ptr<Figure> > optional_taken_figure) {
    auto taking = board->figureAt(to_.getX(), to_.getY()).value();
    board->placeFigure(taking, from_.getX(), from_.getY());
    board->removeFigure(to_.getX(), to_.getY());

    int taken_x = to_.getX();
    int taken_y = (to_.getY() == 2) ? (to_.getY() + 1) : (to_.getY() - 1);
    board->placeFigure(optional_taken_figure.value(), taken_x, taken_y);
}
