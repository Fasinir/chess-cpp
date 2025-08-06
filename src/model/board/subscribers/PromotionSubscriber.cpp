#include "PromotionSubscriber.h"

PromotionSubscriber::PromotionSubscriber(
    std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber) : pawnPositionSubscriber(
    std::move(pawnPositionSubscriber)) {
    this->promotionCoordinates;
}

void PromotionSubscriber::notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) {
    resetPromotionCoordinates();
    int toYCoordinate = applyMoveResult.getMove().getTo().getY();
    if (pawnPositionSubscriber->getPawnPositions().contains(applyMoveResult.getMove().getFrom())
        && (toYCoordinate == 7 || toYCoordinate == 0)) {
        promotionCoordinates = applyMoveResult.getMove().getTo();
    }
}

std::optional<Coordinates> PromotionSubscriber::getPromotionCoordinates() const {
    return promotionCoordinates;
}

void PromotionSubscriber::resetPromotionCoordinates() {
    promotionCoordinates.reset();
}
