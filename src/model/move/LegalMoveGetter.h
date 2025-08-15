#ifndef LEGALMOVEGETTER_H
#define LEGALMOVEGETTER_H
#include <utility>
#include <vector>

#include "DefaultMove.h"
#include "../subscribers/move_subs/KingPositionSubscriber.h"
#include "Move.h"
#include "VisionBoard.h"
#include "../core/ChessBoard.h"
#include "../subscribers/move_subs/CastleSubscriber.h"
#include "../subscribers/move_subs/EnPassantSubscriber.h"
#include "../subscribers/move_subs/PawnPositionSubscriber.h"

class LegalMoveGetter {
    std::shared_ptr<EnPassantSubscriber> en_passant_subscriber_;
    std::shared_ptr<CastleSubscriber> castle_subscriber_;
    std::shared_ptr<KingPositionSubscriber> king_position_subscriber_;
    std::shared_ptr<PawnPositionSubscriber> pawn_position_subscriber_;

    static bool isWithinBounds(int x, int y);

    bool leavesKingSafe(std::shared_ptr<ChessBoard> board, std::shared_ptr<Move> move, ChessColor &color);

    std::optional<std::shared_ptr<Move> > tryCastle(std::shared_ptr<ChessBoard> board, Coordinates king_from,
                                                    bool is_castling_queen_side, const VisionBoard &enemy_vision);

    std::vector<std::shared_ptr<Move> > handlePawnMoves(std::shared_ptr<ChessBoard> board, Coordinates from);

public:
    LegalMoveGetter(std::shared_ptr<EnPassantSubscriber> en_passant_checker,
                    std::shared_ptr<CastleSubscriber> castle_checker,
                    std::shared_ptr<KingPositionSubscriber> king_position_subscriber,
                    std::shared_ptr<PawnPositionSubscriber> pawn_position_subscriber)
        : en_passant_subscriber_(std::move(en_passant_checker)),
          castle_subscriber_(std::move(castle_checker)),
          king_position_subscriber_(std::move(king_position_subscriber)),
          pawn_position_subscriber_(std::move(pawn_position_subscriber)) {
    }

    LegalMoveGetter();

    ~LegalMoveGetter() = default;

    std::vector<std::shared_ptr<Move> > getLegalMovesForColor(std::shared_ptr<ChessBoard> board, ChessColor color);
};


#endif //LEGALMOVEGETTER_H
