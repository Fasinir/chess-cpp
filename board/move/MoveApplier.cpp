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
            break;
        default:
            undoDefaultMove(chessBoard, applyMoveResult);
    }
}

std::unique_ptr<ApplyMoveResult> MoveApplier::handleDefault(ChessBoard &chessBoard, const Move &move) {
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> optionalFromFigure = chessBoard.figureAt(from.getX(), from.getY()).value();
    chessBoard.removeFigure(from.getX(), from.getY());
    const std::shared_ptr<Figure> &fromFigure = optionalFromFigure;
    std::optional<std::shared_ptr<Figure> > optionalToFigure = chessBoard.placeFigure(
        fromFigure,
        to.getX(), to.getY());
    return std::make_unique<ApplyMoveResult>(move, optionalToFigure);
}

std::unique_ptr<ApplyMoveResult> MoveApplier::handleCastle(ChessBoard &chessBoard, const Move &move) {
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> king = chessBoard.figureAt(from.getX(), from.getY()).value();
    chessBoard.placeFigure(king, to.getX(), to.getY());
    chessBoard.removeFigure(from.getX(), from.getY());
    int rookX = from.getX();
    int rookY = to.getY() == 2 ? 0 : 7;
    std::shared_ptr<Figure> rook = chessBoard.figureAt(rookX, rookY).value();
    int newRookY = to.getY() == 2 ? 3 : 5;
    chessBoard.placeFigure(rook, from.getX(), newRookY);
    chessBoard.removeFigure(rookX, rookY);
    return std::make_unique<ApplyMoveResult>(move);
}

std::unique_ptr<ApplyMoveResult> MoveApplier::handleEnPassant(ChessBoard &chessBoard, const Move &move) {
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> fromPawn = chessBoard.figureAt(from.getX(), from.getY()).value();
    chessBoard.placeFigure(fromPawn, to.getX(), to.getY());
    chessBoard.removeFigure(from.getX(), from.getY());
    int takenPawnX = to.getX() == 2
                         ? to.getX() + 1
                         : to.getX() - 1;
    int takenPawnY = to.getY();
    std::optional<std::shared_ptr<Figure> > optionalFromPawn = chessBoard.figureAt(takenPawnX, takenPawnY);
    chessBoard.removeFigure(takenPawnX, takenPawnY);
    return std::make_unique<ApplyMoveResult>(move, optionalFromPawn);
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
    Move move = applyMoveResult.getMove();
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> king = chessBoard.figureAt(to.getX(), to.getY()).value();
    chessBoard.placeFigure(king, from.getX(), from.getY());
    chessBoard.removeFigure(to.getX(), to.getY());

    int currentRookX = to.getX();
    int currentRookY = to.getY() == 2 ? 3 : 5;
    std::shared_ptr<Figure> rook = chessBoard.figureAt(currentRookX, currentRookY).value();
    int newRookX = to.getX();
    int newRookY = to.getY() == 2 ? 0 : 7;
    chessBoard.placeFigure(rook, newRookX, newRookY);
    chessBoard.removeFigure(currentRookX, currentRookY);
}

void MoveApplier::undoEnPassant(ChessBoard &chessBoard, const ApplyMoveResult &applyMoveResult) {
    Move move = applyMoveResult.getMove();
    Coordinates from = move.getFrom();
    Coordinates to = move.getTo();
    std::shared_ptr<Figure> takingPawn = chessBoard.figureAt(to.getX(), to.getY()).value();
    chessBoard.placeFigure(takingPawn, from.getX(), from.getY());
    chessBoard.removeFigure(to.getX(), to.getY());
    int takenPawnX = to.getX() == 2
                         ? to.getX() + 1
                         : to.getX() - 1;
    int takenPawnY = to.getY();
    chessBoard.placeFigure(applyMoveResult.getTakenFigure().value(), takenPawnX, takenPawnY);
}
