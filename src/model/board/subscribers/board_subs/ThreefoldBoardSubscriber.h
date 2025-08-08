#ifndef THREEFOLDSUBSCRIBER_H
#define THREEFOLDSUBSCRIBER_H
#include <unordered_map>

#include "../../ChessBoard.h"
#include "../../../Utils.h"
#include "../move_subs/CastleSubscriber.h"
#include "../move_subs/EnPassantSubscriber.h"


class ThreefoldBoardSubscriber {
    //unsure if size_t is the right choice
    std::unordered_map<std::string, int> positionCountMap;

public:
    ThreefoldBoardSubscriber() = default;

    ~ThreefoldBoardSubscriber() = default;

    bool updateAndCheckIfThreefoldWasReached(const ChessBoard &chessBoard,
                                             const CastleSubscriber &castleSub,
                                             const EnPassantSubscriber &enPassantSub,
                                             bool whiteToMove);
};


#endif //THREEFOLDSUBSCRIBER_H
