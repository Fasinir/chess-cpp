#include "CastleMove.h"
#include "ApplyMoveResult.h"

ApplyMoveResult CastleMove::apply(std::shared_ptr<ChessBoard> board) {
    auto king = board->figureAt(from_).value();
    board->placeFigure(king, to_);
    board->removeFigure(from_);

    int rook_x = (to_.getX() == 2) ? 0 : 7;
    int rook_y = to_.getY();

    auto rook = board->figureAt(Coordinates(rook_x, rook_y)).value();
    int new_rook_x = (to_.getX() == 2) ? 3 : 5;
    board->placeFigure(rook, Coordinates(new_rook_x, from_.getY()));
    board->removeFigure(Coordinates(rook_x, rook_y));

    return ApplyMoveResult(std::const_pointer_cast<Move>(shared_from_this()));
}

void CastleMove::undo(std::shared_ptr<ChessBoard> board,
                      std::optional<std::shared_ptr<Figure> > optional_taken_figure) {
    auto king = board->figureAt(to_).value();
    board->placeFigure(king, from_);
    board->removeFigure(to_);

    int cur_rook_x = (to_.getX() == 2) ? 3 : 5;
    int cur_rook_y = to_.getY();
    auto rook = board->figureAt(Coordinates(cur_rook_x, cur_rook_y)).value();
    int new_rook_x = (to_.getX() == 2) ? 0 : 7;
    board->placeFigure(rook, Coordinates(new_rook_x, to_.getY()));
    board->removeFigure(Coordinates(cur_rook_x, cur_rook_y));
}
