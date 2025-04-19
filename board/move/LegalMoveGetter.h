#ifndef LEGALMOVEGETTER_H
#define LEGALMOVEGETTER_H
#include <vector>

#include "Move.h"
#include "../ChessBoard.h"

class LegalMoveGetter {
    bool isWithinBounds(int x, int y);

    std::vector<Move> handlePawnSingleMove(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnDoubleMove(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnEnPassant(ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnTaking(ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleKnight(ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleDiagonal(ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleStraight(ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleKing(ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleCastle(ChessBoard &chessBoard, Coordinates from);

public:
    explicit LegalMoveGetter() = default;

    ~LegalMoveGetter() = default;

    std::vector<Move> getLegalMovesForCoordinate(ChessBoard &chessBoard, Coordinates from);
};


#endif //LEGALMOVEGETTER_H
