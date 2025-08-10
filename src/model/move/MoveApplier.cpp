#include "MoveApplier.h"

std::unique_ptr<ApplyMoveResult> MoveApplier::applyMove(ChessBoard &chess_board, const Move &move) {
    switch (move.getType()) {
        case MoveType::EN_PASSANT:
            return handleEnPassant(chess_board, move);
        case MoveType::CASTLE:
            return handleCastle(chess_board, move);
        default:
            return handleDefault(chess_board, move);
    }
}

void MoveApplier::undoMove(ChessBoard &chess_board, const ApplyMoveResult &apply_move_result) {
    switch (apply_move_result.getMove().getType()) {
        case MoveType::EN_PASSANT:
            undoEnPassant(chess_board, apply_move_result);
            break;
        case MoveType::CASTLE:
            undoCastleMove(chess_board, apply_move_result);
            break;
        default:
            undoDefaultMove(chess_board, apply_move_result);
    }
}

std::unique_ptr<ApplyMoveResult> MoveApplier::handleDefault(ChessBoard &chess_board, const Move &move) {
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> optional_from_figure = chess_board.figureAt(from.getX(), from.getY()).value();
    chess_board.removeFigure(from.getX(), from.getY());
    const std::shared_ptr<Figure> &from_figure = optional_from_figure;
    std::optional<std::shared_ptr<Figure> > optional_to_figure = chess_board.placeFigure(
        from_figure,
        to.getX(), to.getY());
    return std::make_unique<ApplyMoveResult>(move, optional_to_figure);
}

std::unique_ptr<ApplyMoveResult> MoveApplier::handleCastle(ChessBoard &chess_board, const Move &move) {
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> king = chess_board.figureAt(from.getX(), from.getY()).value();
    chess_board.placeFigure(king, to.getX(), to.getY());
    chess_board.removeFigure(from.getX(), from.getY());
    int rook_x = to.getX() == 2 ? 0 : 7;
    int rook_y = to.getY();
    std::shared_ptr<Figure> rook = chess_board.figureAt(rook_x, rook_y).value();
    int new_rook_x = to.getX() == 2 ? 3 : 5;
    chess_board.placeFigure(rook, new_rook_x, from.getY());
    chess_board.removeFigure(rook_x, rook_y);
    return std::make_unique<ApplyMoveResult>(move);
}

std::unique_ptr<ApplyMoveResult> MoveApplier::handleEnPassant(ChessBoard &chess_board, const Move &move) {
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> from_pawn = chess_board.figureAt(from.getX(), from.getY()).value();
    chess_board.placeFigure(from_pawn, to.getX(), to.getY());
    chess_board.removeFigure(from.getX(), from.getY());
    int taken_pawn_x = to.getX();
    int taken_pawn_y = to.getY() == 2
                         ? to.getY() + 1
                         : to.getY() - 1;
    std::optional<std::shared_ptr<Figure> > optional_from_pawn = chess_board.figureAt(taken_pawn_x, taken_pawn_y);
    chess_board.removeFigure(taken_pawn_x, taken_pawn_y);
    return std::make_unique<ApplyMoveResult>(move, optional_from_pawn);
}

void MoveApplier::undoDefaultMove(ChessBoard &chess_board, const ApplyMoveResult &apply_move_result) {
    Move move = apply_move_result.getMove();
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> to_figure = chess_board.figureAt(to.getX(), to.getY()).value();
    chess_board.placeFigure(to_figure, from.getX(), from.getY());

    if (apply_move_result.getTakenFigure().has_value()) {
        std::shared_ptr<Figure> taken_figure = apply_move_result.getTakenFigure().value();
        chess_board.placeFigure(taken_figure, to.getX(), to.getY());
    } else {
        chess_board.removeFigure(to.getX(), to.getY());
    }
}

void MoveApplier::undoCastleMove(ChessBoard &chess_board, const ApplyMoveResult &apply_move_result) {
    Move move = apply_move_result.getMove();
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> king = chess_board.figureAt(to.getX(), to.getY()).value();
    chess_board.placeFigure(king, from.getX(), from.getY());
    chess_board.removeFigure(to.getX(), to.getY());

    int current_rook_x = to.getX() == 2 ? 3 : 5;
    int current_rook_y = to.getY();
    std::shared_ptr<Figure> rook = chess_board.figureAt(current_rook_x, current_rook_y).value();
    int new_rook_x = to.getX() == 2 ? 0 : 7;
    int new_rook_y = to.getY();
    chess_board.placeFigure(rook, new_rook_x, new_rook_y);
    chess_board.removeFigure(current_rook_x, current_rook_y);
}

void MoveApplier::undoEnPassant(ChessBoard &chess_board, const ApplyMoveResult &apply_move_result) {
    Move move = apply_move_result.getMove();
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> taking_pawn = chess_board.figureAt(to.getX(), to.getY()).value();
    chess_board.placeFigure(taking_pawn, from.getX(), from.getY());
    chess_board.removeFigure(to.getX(), to.getY());
    int taken_pawn_x = to.getX();
    int taken_pawn_y = to.getY() == 2
                         ? to.getY() + 1
                         : to.getY() - 1;
    chess_board.placeFigure(apply_move_result.getTakenFigure().value(), taken_pawn_x, taken_pawn_y);
}
