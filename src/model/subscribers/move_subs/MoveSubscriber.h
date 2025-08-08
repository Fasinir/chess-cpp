#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include "../../move/ApplyMoveResult.h"


class ApplyMoveResult;

class MoveSubscriber {
public:
    MoveSubscriber() = default;

    virtual ~MoveSubscriber() = default;

    virtual void notify(const ApplyMoveResult &applyMoveResult) = 0;
};


#endif //SUBSCRIBER_H
