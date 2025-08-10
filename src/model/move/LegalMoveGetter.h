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

    std::vector<Move> handlePawnSingleMove(const ChessBoard &chess_board, const Coordinates &from);

    std::vector<Move> handlePawnDoubleMove(const ChessBoard &chess_board, const Coordinates &from);

    std::vector<Move> handlePawnEnPassant(const ChessBoard &chess_board, const Coordinates &from);

    std::vector<Move> handlePawnTaking(const ChessBoard &chess_board, const Coordinates &from);

    std::vector<Move> handleKnight(const ChessBoard &chess_board, const Coordinates &from);

    std::vector<Move> handleDiagonal(const ChessBoard &chess_board, const Coordinates &from);

    std::vector<Move> handleStraight(const ChessBoard &chess_board, const Coordinates &from);

    std::vector<Move> handleKing(const ChessBoard &chess_board, const Coordinates &from,
                                 const std::shared_ptr<VisionBoard> &vision_board);

    std::vector<Move> generateCastle(const ChessBoard &chess_board, const Coordinates &from,
                                     const std::shared_ptr<VisionBoard> &vision_board);

    std::vector<Move> generateMoves(const ChessBoard &chess_board, ChessColor color, bool skip_castle,
                                    const std::shared_ptr<VisionBoard> &vision_board);

public:
    LegalMoveGetter(std::shared_ptr<EnPassantSubscriber> en_passant_checker,
                    std::shared_ptr<CastleSubscriber> castle_checker,
                    std::shared_ptr<MoveApplier> move_applier,
                    std::shared_ptr<KingPositionSubscriber> king_position_subscriber)
        : en_passant_subscriber_(std::move(en_passant_checker)),
          castle_checker_(std::move(castle_checker)),
          move_applier_(std::move(move_applier)),
          king_position_subscriber_(std::move(king_position_subscriber)) {
    }

    LegalMoveGetter();

    ~LegalMoveGetter() = default;

    std::vector<Move> generateMovesFromSquare(const ChessBoard &chess_board, const Coordinates &from, bool skip_castle,
                                              const std::shared_ptr<VisionBoard> &vision_board);

    std::vector<Move> getLegalMovesForColor(ChessBoard &chess_board, ChessColor color);
};


#endif //LEGALMOVEGETTER_H
