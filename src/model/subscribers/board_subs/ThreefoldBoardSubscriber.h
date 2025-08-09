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

    bool updateAndCheckIfThreefoldWasReached(const ChessBoard &chessBoard,
                                             const CastleSubscriber &castleSub,
                                             const EnPassantSubscriber &enPassantSub,
                                             bool whiteToMove);
};


#endif //THREEFOLDSUBSCRIBER_H
