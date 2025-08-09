#include "FiftyMoveSubscriber.h"

#include <utility>

FiftyMoveSubscriber::FiftyMoveSubscriber(std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber) {
    this->pawn_position_subscriber_ = std::move(pawnPositionSubscriber);
    this->count_ = 0;
}

void FiftyMoveSubscriber::notify(const ApplyMoveResult &applyMoveResult) {
    if (applyMoveResult.getTakenFigure().has_value()
        || pawn_position_subscriber_->getPawnPositions().contains(applyMoveResult.getMove().getFrom())) {
        count_ = 0;
    } else {
        count_++;
    }
}

bool FiftyMoveSubscriber::fiftyMoveRuleIsReached() const {
    return count_ == 50;
}
