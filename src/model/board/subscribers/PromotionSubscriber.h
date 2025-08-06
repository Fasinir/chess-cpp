#ifndef PROMOTIONSUBSCRIBER_H
#define PROMOTIONSUBSCRIBER_H
#include "PawnPositionSubscriber.h"
#include "Subscriber.h"


class PromotionSubscriber : public Subscriber {
    std::optional<Coordinates> promotionCoordinates;
    std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber;

public:
    explicit PromotionSubscriber(std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber);

    void notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) override;

    std::optional<Coordinates> getPromotionCoordinates() const;

    void resetPromotionCoordinates();
};


#endif //PROMOTIONSUBSCRIBER_H
