#ifndef CASTLEMOVE_H
#define CASTLEMOVE_H
#include "Move.h"


class CastleMove : public Move {
public:
    using Move::Move;

    ApplyMoveResult apply(std::shared_ptr<ChessBoard> board) override;

    void undo(std::shared_ptr<ChessBoard> board, std::optional<std::shared_ptr<Figure> > optional_taken_figure) override;
};


#endif //CASTLEMOVE_H
