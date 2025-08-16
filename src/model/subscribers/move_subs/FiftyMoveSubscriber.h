#ifndef FIFTYMOVESUBSCRIBER_H
#define FIFTYMOVESUBSCRIBER_H

#include "PawnPositionSubscriber.h"
#include "MoveSubscriber.h"


class FiftyMoveSubscriber final : public MoveSubscriber {
    int count_;
    std::shared_ptr<PawnPositionSubscriber> pawn_position_subscriber_;

public:
    explicit FiftyMoveSubscriber(std::shared_ptr<PawnPositionSubscriber> pawn_position_subscriber);

    void notify(const ApplyMoveResult &apply_move_result) override;

    [[nodiscard]] bool isFiftyMoveRuleReached() const;
};


#endif //FIFTYMOVESUBSCRIBER_H
