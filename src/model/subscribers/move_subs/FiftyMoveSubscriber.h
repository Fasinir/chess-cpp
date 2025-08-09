#ifndef FIFTYMOVESUBSCRIBER_H
#define FIFTYMOVESUBSCRIBER_H

#include "PawnPositionSubscriber.h"
#include "MoveSubscriber.h"


class FiftyMoveSubscriber : public MoveSubscriber {
    int count_;
    std::shared_ptr<PawnPositionSubscriber> pawn_position_subscriber_;

public:
    explicit FiftyMoveSubscriber(std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber);

    void notify(const ApplyMoveResult &applyMoveResult) override;

    [[nodiscard]] bool fiftyMoveRuleIsReached() const;
};


#endif //FIFTYMOVESUBSCRIBER_H
