#ifndef LEGALMOVEGETTER_H
#define LEGALMOVEGETTER_H
#include <utility>
#include <vector>

#include "../subscribers/move_subs/KingPositionSubscriber.h"
#include "Move.h"
#include "MoveApplier.h"
#include "VisionBoard.h"
#include "../core/ChessBoard.h"
#include "../subscribers/move_subs/CastleSubscriber.h"
#include "../subscribers/move_subs/EnPassantSubscriber.h"

class LegalMoveGetter {
    std::shared_ptr<EnPassantSubscriber> en_passant_subscriber_;
    std::shared_ptr<CastleSubscriber> castle_checker_;
    std::shared_ptr<MoveApplier> move_applier_;
    std::shared_ptr<KingPositionSubscriber> king_position_subscriber_;

    static bool isWithinBounds(int x, int y);

    std::vector<Move> handlePawnSingleMove(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnDoubleMove(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnEnPassant(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handlePawnTaking(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleKnight(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleDiagonal(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleStraight(const ChessBoard &chessBoard, Coordinates from);

    std::vector<Move> handleKing(const ChessBoard &chessBoard, Coordinates from,
                                 const std::shared_ptr<VisionBoard> &visionBoard);

    std::vector<Move> generateCastle(const ChessBoard &chessBoard, Coordinates from,
                                   const std::shared_ptr<VisionBoard> &visionBoard);

    std::vector<Move> generateMoves(const ChessBoard &chessBoard, ChessColor color, bool skipCastle,
                                    const std::shared_ptr<VisionBoard> &visionBoard);

public:
    LegalMoveGetter(std::shared_ptr<EnPassantSubscriber> enPassantChecker,
                    std::shared_ptr<CastleSubscriber> castleChecker,
                    std::shared_ptr<MoveApplier> moveApplier,
                    std::shared_ptr<KingPositionSubscriber> kingPositionSubscriber)
        : en_passant_subscriber_(std::move(enPassantChecker)),
          castle_checker_(std::move(castleChecker)),
          move_applier_(std::move(moveApplier)),
          king_position_subscriber_(std::move(kingPositionSubscriber)) {
    }

    LegalMoveGetter();

    ~LegalMoveGetter() = default;

    std::vector<Move> generateMovesFromSquare(const ChessBoard &chessBoard, Coordinates from, bool skipCastle,
                                                 const std::shared_ptr<VisionBoard> &visionBoard);

    std::vector<Move> getLegalMovesForColor(ChessBoard &chessBoard, ChessColor color);
};


#endif //LEGALMOVEGETTER_H
