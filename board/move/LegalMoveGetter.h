#ifndef LEGALMOVEGETTER_H
#define LEGALMOVEGETTER_H
#include <vector>

#include "Move.h"
#include "MoveApplier.h"
#include "../ChessBoard.h"
#include "checkers/CastleChecker.h"
#include "checkers/CheckChecker.h"
#include "checkers/DoubleMoveChecker.h"
#include "checkers/EnPassantChecker.h"

class LegalMoveGetter {
    std::shared_ptr<EnPassantChecker> enPassantChecker;
    std::shared_ptr<CheckChecker> checkChecker;
    std::shared_ptr<CastleChecker> castleChecker;
    std::shared_ptr<DoubleMoveChecker> doubleMoveChecker;
    std::shared_ptr<MoveApplier> moveApplier;

    bool isWithinBounds(int x, int y);

    std::vector<Move> handlePawnSingleMove(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnDoubleMove(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnEnPassant(ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnTaking(ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleKnight(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleDiagonal(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleStraight(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleKing(ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleCastle(ChessBoard &chessBoard, Coordinates from);

public:
    LegalMoveGetter(std::shared_ptr<EnPassantChecker> enPassantChecker, std::shared_ptr<CheckChecker> checkChecker,
                    std::shared_ptr<CastleChecker> castleChecker,
                    std::shared_ptr<DoubleMoveChecker> doubleMoveChecker,
                    std::shared_ptr<MoveApplier> moveApplier) : enPassantChecker(enPassantChecker),
                                                                checkChecker(checkChecker),
                                                                castleChecker(castleChecker),
                                                                doubleMoveChecker(doubleMoveChecker),
                                                                moveApplier(moveApplier) {
    }

    ~LegalMoveGetter() = default;

    std::vector<Move> getLegalMovesForCoordinate(ChessBoard &chessBoard, Coordinates from);
};


#endif //LEGALMOVEGETTER_H
