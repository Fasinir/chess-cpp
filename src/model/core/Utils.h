#ifndef UTILS_H
#define UTILS_H
#include <string>

#include "ChessBoard.h"
#include "../subscribers/move_subs/CastleSubscriber.h"
#include "../subscribers/move_subs/EnPassantSubscriber.h"

class Utils {
public:
    static std::string createFEN(const ChessBoard &board, const CastleSubscriber &castleSub,
                                 const EnPassantSubscriber &enPassantSub, bool whiteToMove);

    static ChessColor oppositeColor(ChessColor color);
};


#endif //UTILS_H
