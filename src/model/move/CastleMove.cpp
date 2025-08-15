#include "CastleMove.h"
#include "ApplyMoveResult.h"

ApplyMoveResult CastleMove::apply(ChessBoard &board) {
    auto king = board.figureAt(from_.getX(), from_.getY()).value();
    board.placeFigure(king, to_.getX(), to_.getY());
    board.removeFigure(from_.getX(), from_.getY());

    int rook_x = (to_.getX() == 2) ? 0 : 7;
    int rook_y = to_.getY();

    auto rook = board.figureAt(rook_x, rook_y).value();
    int new_rook_x = (to_.getX() == 2) ? 3 : 5;
    board.placeFigure(rook, new_rook_x, from_.getY());
    board.removeFigure(rook_x, rook_y);

    return ApplyMoveResult(std::const_pointer_cast<Move>(shared_from_this()));
}

void CastleMove::undo(ChessBoard &board, std::optional<std::shared_ptr<Figure> > optional_taken_figure) {
    auto king = board.figureAt(to_.getX(), to_.getY()).value();
    board.placeFigure(king, from_.getX(), from_.getY());
    board.removeFigure(to_.getX(), to_.getY());

    int cur_rook_x = (to_.getX() == 2) ? 3 : 5;
    int cur_rook_y = to_.getY();
    auto rook = board.figureAt(cur_rook_x, cur_rook_y).value();
    int new_rook_x = (to_.getX() == 2) ? 0 : 7;
    board.placeFigure(rook, new_rook_x, to_.getY());
    board.removeFigure(cur_rook_x, cur_rook_y);
}
