#ifndef FIFTYMOVESUBSCRIBER_H
#define FIFTYMOVESUBSCRIBER_H

#include "PawnPositionSubscriber.h"
#include "MoveSubscriber.h"


class FiftyMoveSubscriber : public MoveSubscriber {
    int count;
    std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber;

public:
    explicit FiftyMoveSubscriber(std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber);

    void notify(const ApplyMoveResult &applyMoveResult) override;

    bool fiftyMoveRuleIsReached() const;
};


#endif //FIFTYMOVESUBSCRIBER_H
