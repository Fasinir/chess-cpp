#ifndef UTILS_H
#define UTILS_H
#include <string>

#include "board/ChessBoard.h"
#include "board/subscribers/move_subs/CastleSubscriber.h"
#include "board/subscribers/move_subs/EnPassantSubscriber.h"

class Utils {
public:
    static std::string createFEN(const ChessBoard &board, const CastleSubscriber &castleSub,
                                 const EnPassantSubscriber &enPassantSub, bool whiteToMove);
};


#endif //UTILS_H
