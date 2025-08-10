#ifndef MOVEAPPLIER_H
#define MOVEAPPLIER_H
#include "ApplyMoveResult.h"
#include "../core/ChessBoard.h"


class MoveApplier {
    std::unique_ptr<ApplyMoveResult> handleDefault(ChessBoard &chess_board, const Move &move);

    std::unique_ptr<ApplyMoveResult> handleCastle(ChessBoard &chess_board, const Move &move);

    std::unique_ptr<ApplyMoveResult> handleEnPassant(ChessBoard &chess_board, const Move &move);

    void undoDefaultMove(ChessBoard &chess_board, const ApplyMoveResult &apply_move_result);

    void undoCastleMove(ChessBoard &chess_board, const ApplyMoveResult &apply_move_result);

    void undoEnPassant(ChessBoard &chess_board, const ApplyMoveResult &apply_move_result);

public:
    MoveApplier() = default;

    std::unique_ptr<ApplyMoveResult> applyMove(ChessBoard &chess_board, const Move &move);

    void undoMove(ChessBoard &chess_board, const ApplyMoveResult &apply_move_result);

    ~MoveApplier() = default;
};


#endif //MOVEAPPLIER_H
