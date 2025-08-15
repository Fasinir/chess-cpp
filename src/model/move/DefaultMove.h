#ifndef DEFAULTMOVE_H
#define DEFAULTMOVE_H
#include "Move.h"


class DefaultMove : public Move {
public:
    using Move::Move;

    ApplyMoveResult apply(ChessBoard &board) override;

    void undo(ChessBoard &board, std::optional<std::shared_ptr<Figure> > optional_taken_figure) override;
};


#endif //DEFAULTMOVE_H
