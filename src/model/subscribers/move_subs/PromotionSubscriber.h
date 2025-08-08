#ifndef PROMOTIONSUBSCRIBER_H
#define PROMOTIONSUBSCRIBER_H
#include "PawnPositionSubscriber.h"
#include "MoveSubscriber.h"


class PromotionSubscriber : public MoveSubscriber {
    std::optional<Coordinates> promotionCoordinates;
    std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber;

public:
    explicit PromotionSubscriber(std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber);

    void notify(const ApplyMoveResult &applyMoveResult) override;

    [[nodiscard]] std::optional<Coordinates> getPromotionCoordinates() const;

    void resetPromotionCoordinates();
};


#endif //PROMOTIONSUBSCRIBER_H
