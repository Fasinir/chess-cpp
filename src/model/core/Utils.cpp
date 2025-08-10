#include "Utils.h"

#include "Constants.h"
#include "../move/Coordinates.h"

#include <string>
#include <sstream>
#include "../subscribers/move_subs/CastleSubscriber.h"
#include "../subscribers/move_subs/EnPassantSubscriber.h"

std::string Utils::createFEN(const ChessBoard &board, const CastleSubscriber &castle_sub,
                             const EnPassantSubscriber &en_passant_sub, bool white_to_move) {
    std::ostringstream fen;

    // 1. Piece placement
    fen << board.toFENBoardPart();

    // 2. Active color
    fen << " " << (white_to_move ? "w" : "b");

    // 3. Castling availability
    std::string castling;
    if (castle_sub.canCastle(Coordinates(6, 0))) castling.push_back('K');
    if (castle_sub.canCastle(Coordinates(2, 0))) castling.push_back('Q');
    if (castle_sub.canCastle(Coordinates(6, 7))) castling.push_back('k');
    if (castle_sub.canCastle(Coordinates(2, 7))) castling.push_back('q');
    fen << " " << (castling.empty() ? "-" : castling);

    // 4. En passant target square
    if (auto ep = en_passant_sub.getEnPassantCoordinates(); ep.has_value()) {
        fen << " " << ep->toAlgebraicNotation();
    } else {
        fen << " -";
    }

    // (5 and 6 halfmove / fullmove counters — optional for you right now)
    // We'll skip for now, but we could append " 0 1" if needed.
    return fen.str();
}

ChessColor Utils::oppositeColor(const ChessColor &color) {
    return color == ChessColor::WHITE ? ChessColor::BLACK : ChessColor::WHITE;
}
