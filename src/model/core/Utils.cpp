#include "Utils.h"

#include "Constants.h"
#include "../move/Coordinates.h"

#include <string>
#include <sstream>
#include "../subscribers/move_subs/CastleSubscriber.h"
#include "../subscribers/move_subs/EnPassantSubscriber.h"

std::string Utils::createFEN(const ChessBoard &board, const CastleSubscriber &castleSub,
                             const EnPassantSubscriber &enPassantSub, bool whiteToMove) {
    std::ostringstream fen;

    // 1. Piece placement
    fen << board.toFENBoardPart();

    // 2. Active color
    fen << " " << (whiteToMove ? "w" : "b");

    // 3. Castling availability
    std::string castling;
    if (castleSub.canCastle(Coordinates(6, 0))) castling.push_back('K');
    if (castleSub.canCastle(Coordinates(2, 0))) castling.push_back('Q');
    if (castleSub.canCastle(Coordinates(6, 7))) castling.push_back('k');
    if (castleSub.canCastle(Coordinates(2, 7))) castling.push_back('q');
    fen << " " << (castling.empty() ? "-" : castling);

    // 4. En passant target square
    if (auto ep = enPassantSub.getEnPassantCoordinates(); ep.has_value()) {
        fen << " " << ep->toAlgebraicNotation();
    } else {
        fen << " -";
    }

    // (5 and 6 halfmove / fullmove counters — optional for you right now)
    // We'll skip for now, but we could append " 0 1" if needed.
    return fen.str();
}

ChessColor Utils::oppositeColor(const ChessColor color) {
    return color == ChessColor::WHITE ? ChessColor::BLACK : ChessColor::WHITE;
}
