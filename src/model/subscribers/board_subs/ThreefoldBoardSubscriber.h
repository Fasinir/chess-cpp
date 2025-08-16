#ifndef THREEFOLDSUBSCRIBER_H
#define THREEFOLDSUBSCRIBER_H
#include <unordered_map>

#include "../../core/ChessBoard.h"
#include "../../core/Utils.h"
#include "../move_subs/CastleSubscriber.h"
#include "../move_subs/EnPassantSubscriber.h"


class ThreefoldBoardSubscriber {
    std::unordered_map<std::string, int> position_count_map_;

public:
    ThreefoldBoardSubscriber() = default;

    ~ThreefoldBoardSubscriber() = default;

    bool updateAndCheckThreefold(std::shared_ptr<ChessBoard> chess_board,
                                             std::shared_ptr<CastleSubscriber> castle_sub,
                                             std::shared_ptr<EnPassantSubscriber> en_passant_sub,
                                             bool white_to_move);
};


#endif //THREEFOLDSUBSCRIBER_H
