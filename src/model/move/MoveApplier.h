#ifndef MOVEAPPLIER_H
#define MOVEAPPLIER_H
#include "ApplyMoveResult.h"
#include "../core/ChessBoard.h"


class MoveApplier {
    std::unique_ptr<ApplyMoveResult> handleDefault(ChessBoard &chessBoard, const Move &move);

    std::unique_ptr<ApplyMoveResult> handleCastle(ChessBoard &chessBoard, const Move &move);

    std::unique_ptr<ApplyMoveResult> handleEnPassant(ChessBoard &chessBoard, const Move &move);

    void undoDefaultMove(ChessBoard &chessBoard, const ApplyMoveResult &applyMoveResult);

    void undoCastleMove(ChessBoard &chessBoard, const ApplyMoveResult &applyMoveResult);

    void undoEnPassant(ChessBoard &chessBoard, const ApplyMoveResult &applyMoveResult);

public:
    MoveApplier() = default;

    std::unique_ptr<ApplyMoveResult> applyMove(ChessBoard &chessBoard, const Move &move);

    void undoMove(ChessBoard &chessBoard, const ApplyMoveResult &applyMoveResult);

    ~MoveApplier() = default;
};


#endif //MOVEAPPLIER_H
