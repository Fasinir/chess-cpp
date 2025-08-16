#include "EnPassantMove.h"
#include "ApplyMoveResult.h"

ApplyMoveResult EnPassantMove::apply(std::shared_ptr<ChessBoard> board) {
    auto pawn = board->figureAt(from_).value();
    board->placeFigure(pawn, to_);
    board->removeFigure(from_);

    int taken_x = to_.getX();
    int taken_y = (to_.getY() == Constants::kWhiteEnPassantTakingRank) ? (to_.getY() + 1) : (to_.getY() - 1);
    auto taken = board->figureAt(Coordinates(taken_x, taken_y));
    board->removeFigure(Coordinates(taken_x, taken_y));

    return ApplyMoveResult(std::const_pointer_cast<Move>(shared_from_this()), taken);
}

void EnPassantMove::undo(std::shared_ptr<ChessBoard> board,
                         std::optional<std::shared_ptr<Figure> > optional_taken_figure) {
    auto taking = board->figureAt(to_).value();
    board->placeFigure(taking, from_);
    board->removeFigure(to_);

    int taken_x = to_.getX();
    int taken_y = (to_.getY() == Constants::kWhiteEnPassantTakingRank) ? (to_.getY() + 1) : (to_.getY() - 1);
    board->placeFigure(optional_taken_figure.value(), Coordinates(taken_x, taken_y));
}
