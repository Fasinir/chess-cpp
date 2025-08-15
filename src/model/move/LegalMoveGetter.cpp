#include "LegalMoveGetter.h"

#include "CastleMove.h"
#include "DefaultMove.h"
#include "EnPassantMove.h"
#include "VisionBoard.h"
#include "../core/Utils.h"

bool LegalMoveGetter::isWithinBounds(int x, int y) {
    return x >= 0 && y >= 0 && x < Constants::kBoardSize && y < Constants::kBoardSize;
}

bool LegalMoveGetter::leavesKingSafe(std::shared_ptr<ChessBoard> board, std::shared_ptr<Move> move, ChessColor &color) {
    auto apply_result = move->apply(board);
    VisionBoard enemy_pre(board, Utils::oppositeColor(color));
    Coordinates king_pos = king_position_subscriber_->getKingCoordinates(color);
    if (move->getFrom() == king_pos)
        king_pos = move->getTo();
    bool safe = !enemy_pre.attacks(king_pos);
    move->undo(board, apply_result.getTakenFigure());
    return safe;
}

std::optional<std::shared_ptr<Move> > LegalMoveGetter::tryCastle(std::shared_ptr<ChessBoard> board, Coordinates king_from,
                                                                 bool is_castling_queen_side,
                                                                 const VisionBoard &enemy_vision) {
    int y = king_from.getY();
    int dest_x = is_castling_queen_side ? 2 : 6;
    Coordinates dest(dest_x, y);

    if (!castle_subscriber_->canCastle(dest)) return std::nullopt;
    if (enemy_vision.attacks(king_from)) return std::nullopt;

    int empty_start = is_castling_queen_side ? 1 : 5;
    int empty_end = is_castling_queen_side ? 3 : 6;
    for (int i = empty_start; i <= empty_end; ++i)
        if (board->figureAt(i, y).has_value())
            return std::nullopt;

    int no_check_start = is_castling_queen_side ? 2 : 5;
    int no_check_end = is_castling_queen_side ? 4 : 6;
    for (int i = no_check_start; i <= no_check_end; ++i)
        if (enemy_vision.attacks(Coordinates(i, y)))
            return std::nullopt;

    return std::make_shared<CastleMove>(king_from, dest, "castle");
}

std::vector<std::shared_ptr<Move> > LegalMoveGetter::handlePawnMoves(std::shared_ptr<ChessBoard> board, Coordinates from) {
    int x = from.getX();
    int y = from.getY();
    ChessColor color = board->figureAt(x, y).value()->getColor();
    std::vector<std::shared_ptr<Move> > pawn_moves;

    int dir = (color == ChessColor::kWhite) ? 1 : -1;

    int y1 = y + dir;
    if (isWithinBounds(x, y1) && !board->figureAt(x, y1).has_value()) {
        auto m1 = std::make_shared<DefaultMove>(from, Coordinates{x, y1}, "pawn push");
        if (leavesKingSafe(board, m1, color))
            pawn_moves.emplace_back(std::move(m1));

        bool on_start = (y == 1 && color == ChessColor::kWhite) || (
                            y == 6 && color == ChessColor::kBlack);
        int y2 = y + 2 * dir;
        if (on_start && isWithinBounds(x, y2) && !board->figureAt(x, y2).has_value()) {
            auto m2 = std::make_shared<DefaultMove>(from, Coordinates{x, y2}, "pawn double push");
            if (leavesKingSafe(board, m2, color))
                pawn_moves.emplace_back(std::move(m2));
        }
    }

    int cap_y = y + dir;
    for (int dx: {-1, 1}) {
        int cx = x + dx;
        if (!isWithinBounds(cx, cap_y)) continue;
        Coordinates to{cx, cap_y};
        if (en_passant_subscriber_->canBeTakenEnPassant(to)) {
            auto m = std::make_shared<EnPassantMove>(from, to, "en passant");
            if (leavesKingSafe(board, m, color))
                pawn_moves.emplace_back(std::move(m));
        }
    }

    // pawn taking regularly
    std::shared_ptr<Figure> pawn = board->figureAt(x, y).value();
    for (auto taking_move: pawn->getVision(board, from)) {
        if (board->figureAt(taking_move.getX(), taking_move.getY()).has_value()
            && board->figureAt(taking_move.getX(), taking_move.getY()).value()->getColor() ==
            Utils::oppositeColor(color)) {
            pawn_moves.emplace_back(std::make_shared<DefaultMove>(from, taking_move, "pawn taking"));
        }
    }
    return pawn_moves;
}


std::vector<std::shared_ptr<Move> > LegalMoveGetter::getLegalMovesForColor(std::shared_ptr<ChessBoard> board, ChessColor color) {
    std::vector<std::shared_ptr<Move> > legal;
    VisionBoard enemy_pre(board, Utils::oppositeColor(color));

    for (int x = 0; x < Constants::kBoardSize; ++x) {
        for (int y = 0; y < Constants::kBoardSize; ++y) {
            Coordinates from{x, y};
            auto f = board->figureAt(x, y);
            if (!f.has_value() || f.value()->getColor() != color) continue;

            if (pawn_position_subscriber_->getPawnPositions().contains(from)) {
                for (auto pawn_move: handlePawnMoves(board, from)) {
                    legal.emplace_back(pawn_move);
                }
                continue;
            }

            for (auto to: f.value()->getVision(board, from)) {
                auto occ = board->figureAt(to.getX(), to.getY());
                if (occ.has_value() && occ.value()->getColor() == color) continue;

                auto mv = std::make_shared<DefaultMove>(from, to, "regular");
                if (leavesKingSafe(board, mv, color))
                    legal.emplace_back(std::move(mv));
            }

            if (king_position_subscriber_->getKingCoordinates(color) == from
                && !enemy_pre.attacks(from)) {
                if (auto m = tryCastle(board, from, true, enemy_pre)) {
                    legal.emplace_back(std::move(*m));
                }
                if (auto m = tryCastle(board, from, false, enemy_pre)) {
                    legal.emplace_back(std::move(*m));
                }
            }
        }
    }
    return legal;
}

LegalMoveGetter::LegalMoveGetter() {
    this->en_passant_subscriber_ = std::make_unique<EnPassantSubscriber>();
    this->castle_subscriber_ = std::make_unique<CastleSubscriber>();
    this->king_position_subscriber_ = std::make_unique<KingPositionSubscriber>();
    this->pawn_position_subscriber_ = std::make_unique<PawnPositionSubscriber>(en_passant_subscriber_);
}
