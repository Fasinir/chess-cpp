#ifndef ENPASSANTMOVE_H
#define ENPASSANTMOVE_H
#include "Move.h"


class EnPassantMove : public Move {
public:
    using Move::Move;

    ApplyMoveResult apply(std::shared_ptr<ChessBoard> board) override;

    void undo(std::shared_ptr<ChessBoard> board, std::optional<std::shared_ptr<Figure> > optional_taken_figure) override;
};


#endif //ENPASSANTMOVE_H
