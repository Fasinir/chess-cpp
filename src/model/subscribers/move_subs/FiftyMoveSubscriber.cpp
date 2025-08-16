#include "FiftyMoveSubscriber.h"

#include <utility>

FiftyMoveSubscriber::FiftyMoveSubscriber(std::shared_ptr<PawnPositionSubscriber> pawn_position_subscriber) {
    this->pawn_position_subscriber_ = std::move(pawn_position_subscriber);
    this->count_ = 0;
}

void FiftyMoveSubscriber::notify(const ApplyMoveResult &apply_move_result) {
    if (apply_move_result.getTakenFigure().has_value()
        || pawn_position_subscriber_->getPawnPositions().contains(apply_move_result.getMove()->getFrom())) {
        count_ = 0;
    } else {
        count_++;
    }
}

bool FiftyMoveSubscriber::isFiftyMoveRuleReached() const {
    return count_ == Constants::kFiftyMoveLimit;
}
