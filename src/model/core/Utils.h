#ifndef UTILS_H
#define UTILS_H
#include <string>

#include "ChessBoard.h"
#include "../subscribers/move_subs/CastleSubscriber.h"
#include "../subscribers/move_subs/EnPassantSubscriber.h"

class Utils {
public:
    static std::string createFEN(const ChessBoard &board, const CastleSubscriber &castle_sub,
                                 const EnPassantSubscriber &en_passant_sub, bool white_to_move);

    static ChessColor oppositeColor(const ChessColor &color);
};


#endif //UTILS_H
