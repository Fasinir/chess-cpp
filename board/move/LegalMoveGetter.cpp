#include "LegalMoveGetter.h"

bool LegalMoveGetter::isWithinBounds(int x, int y) {
    return x >= 0 && y >= 0 && x < Constants::BOARD_SIZE && y < Constants::BOARD_SIZE;
}

std::vector<Move> LegalMoveGetter::getLegalMovesForCoordinate(ChessBoard &chessBoard, Coordinates from) {
    // TODO: make it a visitor pattern
    if (!chessBoard.figureAt(from.getX(), from.getY()).has_value())
        return {};
    std::shared_ptr<Figure> figure = chessBoard.figureAt(from.getX(), from.getY()).value();
    std::vector<Move> legalMoves{};
    for (auto moveType: figure->getMoves()) {
        std::vector<Move> toAdd;
        switch (moveType) {
            case MoveType::PAWN_SINGLE_MOVE:
                toAdd = handlePawnSingleMove(chessBoard, from);
                break;
            case MoveType::PAWN_DOUBLE_MOVE:
                toAdd = handlePawnDoubleMove(chessBoard, from);
                break;
            case MoveType::PAWN_TAKING:
                toAdd = handlePawnTaking(chessBoard, from);
                break;
            case MoveType::EN_PASSANT:
                toAdd = handlePawnEnPassant(chessBoard, from);
                break;
            case MoveType::KNIGHT:
                toAdd = handleKnight(chessBoard, from);
                break;
            case MoveType::BISHOP:
                toAdd = handleDiagonal(chessBoard, from);
                break;
            case MoveType::ROOK:
                toAdd = handleStraight(chessBoard, from);
            case MoveType::KING:
                toAdd = handleKing(chessBoard, from);
                break;
            case MoveType::CASTLE:
                toAdd = handleCastle(chessBoard, from);
                break;
            default:
                throw std::invalid_argument("Illegal move type");
        }
        for (auto move: toAdd) {
            // TODO add a check checker call
            legalMoves.emplace_back(move);
        }
    }
    return legalMoves;
}


std::vector<Move> LegalMoveGetter::handlePawnSingleMove(const ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    std::shared_ptr<Figure> pawn = chessBoard.figureAt(from.getX(), from.getY()).value();
    int destinationX = pawn->getColor() == ChessColor::WHITE
                           ? from.getX() + 1
                           : from.getX() - 1;
    int destinationY = from.getY();
    if (isWithinBounds(destinationX, destinationY)
        && !chessBoard.figureAt(destinationX, destinationY).has_value()) {
        legalMoves.emplace_back(from, Coordinates(destinationX, destinationY), MoveType::PAWN_SINGLE_MOVE);
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handlePawnDoubleMove(const ChessBoard &chessBoard, Coordinates from) {
    //TODO: add a check from double move manager
    std::vector<Move> legalMoves{};
    std::shared_ptr<Figure> pawn = chessBoard.figureAt(from.getX(), from.getY()).value();
    int firstX = pawn->getColor() == ChessColor::WHITE
                     ? from.getX() + 1
                     : from.getX() - 1;
    int firstY = from.getY();
    int secondX = pawn->getColor() == ChessColor::WHITE
                      ? from.getX() + 2
                      : from.getX() - 2;
    int secondY = from.getY();
    if (isWithinBounds(secondX, secondY)
        && !chessBoard.figureAt(firstX, firstY).has_value()
        && !chessBoard.figureAt(secondX, secondY).has_value()) {
        legalMoves.emplace_back(from, Coordinates(secondX, secondY), MoveType::PAWN_DOUBLE_MOVE);
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handlePawnEnPassant(ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    if (from.getY() == 3 || from.getY() == 4) {
        // TODO: add a check from en passant checker
        // if (enPassantChecker.getEnPassantField().hasValue())
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handlePawnTaking(ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    std::shared_ptr<Figure> pawn = chessBoard.figureAt(from.getX(), from.getY()).value();
    int destinationX = pawn->getColor() == ChessColor::WHITE
                           ? from.getX() + 1
                           : from.getX() - 1;
    int destinationYOne = from.getY() + 1;
    int destinationYTwo = from.getY() - 1;
    if (isWithinBounds(destinationX, destinationYOne)
        && chessBoard.figureAt(destinationX, destinationYOne).has_value()) {
        legalMoves.emplace_back(from, Coordinates(destinationX, destinationYOne), MoveType::PAWN_TAKING);
    }
    if (isWithinBounds(destinationX, destinationYTwo)
        && chessBoard.figureAt(destinationX, destinationYTwo).has_value()) {
        legalMoves.emplace_back(from, Coordinates(destinationX, destinationYTwo), MoveType::PAWN_TAKING);
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handleKnight(ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    int xDiff[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yDiff[] = {1, 2, 2, 1, -1, -2, -2, -1};
    std::shared_ptr<Figure> knight = chessBoard.figureAt(from.getX(), from.getY()).value();
    for (int i = 0; i < 8; i++) {
        Coordinates coordinates = Coordinates(from.getX() + xDiff[i], from.getY() + yDiff[i]);
        if (isWithinBounds(coordinates.getX(), coordinates.getY())) {
            if (chessBoard.figureAt(coordinates.getX(), coordinates.getY()).has_value()) {
                if (const std::shared_ptr<Figure> figure = chessBoard.figureAt(coordinates.getX(), coordinates.getY()).value(); figure->getColor() != knight->getColor()) {
                    legalMoves.emplace_back(from, coordinates, MoveType::KNIGHT);
                }
            } else {
                legalMoves.emplace_back(from, coordinates, MoveType::KNIGHT);
            }
        }
    }
}

std::vector<Move> LegalMoveGetter::handleDiagonal(ChessBoard &chessBoard, Coordinates from) {
}

std::vector<Move> LegalMoveGetter::handleStraight(ChessBoard &chessBoard, Coordinates from) {
}

std::vector<Move> LegalMoveGetter::handleKing(ChessBoard &chessBoard, Coordinates from) {
}

std::vector<Move> LegalMoveGetter::handleCastle(ChessBoard &chessBoard, Coordinates from) {
    // TODO: add a check from castle checker
}
