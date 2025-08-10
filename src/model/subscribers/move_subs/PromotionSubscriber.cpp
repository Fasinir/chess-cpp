#include "PromotionSubscriber.h"

PromotionSubscriber::PromotionSubscriber(
    std::shared_ptr<PawnPositionSubscriber> pawn_position_subscriber) : pawn_position_subscriber_(
    std::move(pawn_position_subscriber)) {
    this->promotion_coordinates_;
}

void PromotionSubscriber::notify(const ApplyMoveResult &apply_move_result) {
    int to_y_coordinate = apply_move_result.getMove().getTo().getY();
    if (pawn_position_subscriber_->getPawnPositions().contains(apply_move_result.getMove().getFrom())
        && (to_y_coordinate == 7 || to_y_coordinate == 0)) {
        promotion_coordinates_ = apply_move_result.getMove().getTo();
    }
}

std::optional<Coordinates> PromotionSubscriber::getPromotionCoordinates() const {
    return promotion_coordinates_;
}

void PromotionSubscriber::resetPromotionCoordinates() {
    promotion_coordinates_.reset();
}
