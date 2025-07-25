#ifndef LEGALMOVEGETTER_H
#define LEGALMOVEGETTER_H
#include <vector>

#include "../subscribers/KingPositionSubscriber.h"
#include "Move.h"
#include "MoveApplier.h"
#include "../ChessBoard.h"
#include "../subscribers/CastleSubscriber.h"
#include "../subscribers/EnPassantSubscriber.h"

class LegalMoveGetter {
    std::shared_ptr<EnPassantSubscriber> enPassantSubscriber;
    std::shared_ptr<CastleSubscriber> castleChecker;
    std::shared_ptr<MoveApplier> moveApplier;
    std::shared_ptr<KingPositionSubscriber> kingPositionSubscriber;

    static bool isWithinBounds(int x, int y);

    std::vector<Move> handlePawnSingleMove(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnDoubleMove(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnEnPassant(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnTaking(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleKnight(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleDiagonal(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleStraight(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleKing(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleCastle(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> generateMoves(const ChessBoard &chessBoard, ChessColor color);


public:
    LegalMoveGetter(std::shared_ptr<EnPassantSubscriber> enPassantChecker,
                    std::shared_ptr<CastleSubscriber> castleChecker,
                    std::shared_ptr<MoveApplier> moveApplier,
                    std::shared_ptr<KingPositionSubscriber> kingPositionSubscriber)
        : enPassantSubscriber(enPassantChecker),
          castleChecker(castleChecker),
          moveApplier(moveApplier),
          kingPositionSubscriber(kingPositionSubscriber) {
    }

    LegalMoveGetter();

    ~LegalMoveGetter() = default;

    std::vector<Move> getMovesForCoordinate(const ChessBoard &chessBoard, Coordinates from);
    std::vector<Move> getMovesForCoordinate(const ChessBoard &chessBoard, Coordinates from, bool skipCastle);

    std::vector<Move> getLegalMovesForColor(ChessBoard &chessBoard, ChessColor color);
    bool hasVisionOn(const ChessBoard &chessBoard, ChessColor color, Coordinates coordinates);

};


#endif //LEGALMOVEGETTER_H
