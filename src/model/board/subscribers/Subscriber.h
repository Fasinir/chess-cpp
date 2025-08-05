#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include "../ChessBoard.h"
#include "../move/ApplyMoveResult.h"


class Subscriber {
public:
    Subscriber() = default;

    virtual ~Subscriber() = default;

    virtual void notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) = 0;
};


#endif //SUBSCRIBER_H
