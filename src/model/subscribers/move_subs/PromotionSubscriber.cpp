#include "PromotionSubscriber.h"

PromotionSubscriber::PromotionSubscriber(
    std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber) : pawn_position_subscriber_(
    std::move(pawnPositionSubscriber)) {
    this->promotion_coordinates_;
}

void PromotionSubscriber::notify(const ApplyMoveResult &applyMoveResult) {
    int toYCoordinate = applyMoveResult.getMove().getTo().getY();
    if (pawn_position_subscriber_->getPawnPositions().contains(applyMoveResult.getMove().getFrom())
        && (toYCoordinate == 7 || toYCoordinate == 0)) {
        promotion_coordinates_ = applyMoveResult.getMove().getTo();
    }
}

std::optional<Coordinates> PromotionSubscriber::getPromotionCoordinates() const {
    return promotion_coordinates_;
}

void PromotionSubscriber::resetPromotionCoordinates() {
    promotion_coordinates_.reset();
}
