#include "Utils.h"

#include <string>
#include <sstream>
#include "../subscribers/move_subs/CastleSubscriber.h"
#include "../subscribers/move_subs/EnPassantSubscriber.h"

std::string Utils::createFEN(std::shared_ptr<ChessBoard> board, std::shared_ptr<CastleSubscriber> castle_sub,
                             std::shared_ptr<EnPassantSubscriber> en_passant_sub, bool white_to_move) {
    std::ostringstream fen;

    fen << board->toFENBoardPart();

    fen << " " << (white_to_move ? "w" : "b");

    std::string castling;
    if (castle_sub->canCastle(Coordinates(6, 0))) castling.push_back('K');
    if (castle_sub->canCastle(Coordinates(2, 0))) castling.push_back('Q');
    if (castle_sub->canCastle(Coordinates(6, 7))) castling.push_back('k');
    if (castle_sub->canCastle(Coordinates(2, 7))) castling.push_back('q');
    fen << " " << (castling.empty() ? "-" : castling);

    if (auto ep = en_passant_sub->getEnPassantCoordinates(); ep.has_value()) {
        fen << " " << ep->toAlgebraicNotation();
    } else {
        fen << " -";
    }

    return fen.str();
}

ChessColor Utils::oppositeColor(const ChessColor &color) {
    return color == ChessColor::kWhite ? ChessColor::kBlack : ChessColor::kWhite;
}
