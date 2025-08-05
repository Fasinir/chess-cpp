#ifndef FIFTYMOVESUBSCRIBER_H
#define FIFTYMOVESUBSCRIBER_H
#include <vector>

#include "PawnPositionSubscriber.h"
#include "Subscriber.h"


class FiftyMoveSubscriber : public Subscriber {
    int count;
    std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber;

public:
    explicit FiftyMoveSubscriber(std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber);

    void notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) override;

    bool fiftyMoveRuleIsReached();
};


#endif //FIFTYMOVESUBSCRIBER_H
