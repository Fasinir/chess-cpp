#include "MoveApplier.h"

std::unique_ptr<ApplyMoveResult> MoveApplier::applyMove(ChessBoard &chessBoard, const Move &move) {
    switch (move.getType()) {
        case MoveType::EN_PASSANT:
            return handleEnPassant(chessBoard, move);
        case MoveType::CASTLE:
            return handleCastle(chessBoard, move);
        default:
            return handleDefault(chessBoard, move);
    }
}

void MoveApplier::undoMove(ChessBoard &chessBoard, const ApplyMoveResult &applyMoveResult) {
    switch (applyMoveResult.getMove().getType()) {
        case MoveType::EN_PASSANT:
            undoEnPassant(chessBoard, applyMoveResult);
            break;
        case MoveType::CASTLE:
            undoCastleMove(chessBoard, applyMoveResult);
        default:
            undoDefaultMove(chessBoard, applyMoveResult);
    }
}

std::unique_ptr<ApplyMoveResult> MoveApplier::handleDefault(ChessBoard &chessBoard, const Move &move) {
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::optional<std::shared_ptr<Figure> > optionalFromFigure = chessBoard.figureAt(from.getX(), from.getY());
    if (!optionalFromFigure.has_value()) {
        throw std::invalid_argument("From figure does not exist");
    }
    chessBoard.removeFigure(from.getX(), from.getY());
    const std::shared_ptr<Figure> &fromFigure = optionalFromFigure.value();
    std::optional<std::shared_ptr<Figure> > optionalToFigure = chessBoard.placeFigure(
        fromFigure,
        to.getX(), to.getY());
    return std::make_unique<ApplyMoveResult>(move, optionalToFigure);
}

std::unique_ptr<ApplyMoveResult> MoveApplier::handleCastle(ChessBoard &board, const Move &move) {
    return std::make_unique<ApplyMoveResult>(move);
}

std::unique_ptr<ApplyMoveResult> MoveApplier::handleEnPassant(ChessBoard &chessBoard, const Move &move) {
    return std::make_unique<ApplyMoveResult>(move);
}

void MoveApplier::undoDefaultMove(ChessBoard &chessBoard, const ApplyMoveResult &applyMoveResult) {
    Move move = applyMoveResult.getMove();
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> toFigure = chessBoard.figureAt(to.getX(), to.getY()).value();
    chessBoard.placeFigure(toFigure, from.getX(), from.getY());

    if (applyMoveResult.getTakenFigure().has_value()) {
        std::shared_ptr<Figure> takenFigure = applyMoveResult.getTakenFigure().value();
        chessBoard.placeFigure(takenFigure, to.getX(), to.getY());
    } else {
        chessBoard.removeFigure(to.getX(), to.getY());
    }
}

void MoveApplier::undoCastleMove(ChessBoard &chessBoard, const ApplyMoveResult &applyMoveResult) {
}

void MoveApplier::undoEnPassant(ChessBoard &chessBoard, const ApplyMoveResult &applyMoveResult) {
}
