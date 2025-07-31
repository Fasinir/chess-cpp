#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include "../ChessBoard.h"
#include "../move/Move.h"


class Subscriber {
public:
    Subscriber() = default;

    virtual ~Subscriber() = default;

    virtual void notify(Move move, const ChessBoard &chessBoard) = 0;
};


#endif //SUBSCRIBER_H
