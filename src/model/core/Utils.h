#ifndef UTILS_H
#define UTILS_H
#include <string>

#include "ChessBoard.h"
#include "../subscribers/move_subs/CastleSubscriber.h"
#include "../subscribers/move_subs/EnPassantSubscriber.h"

class Utils {
public:
    static std::string createFEN(std::shared_ptr<ChessBoard> board, std::shared_ptr<CastleSubscriber> castle_sub,
                                 std::shared_ptr<EnPassantSubscriber> en_passant_sub, bool white_to_move);

    static ChessColor oppositeColor(const ChessColor &color);
};


#endif //UTILS_H
