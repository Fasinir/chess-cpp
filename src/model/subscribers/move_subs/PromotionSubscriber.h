#ifndef PROMOTIONSUBSCRIBER_H
#define PROMOTIONSUBSCRIBER_H
#include "PawnPositionSubscriber.h"
#include "MoveSubscriber.h"


class PromotionSubscriber final : public MoveSubscriber {
    std::optional<Coordinates> promotion_coordinates_;
    std::shared_ptr<PawnPositionSubscriber> pawn_position_subscriber_;

public:
    explicit PromotionSubscriber(std::shared_ptr<PawnPositionSubscriber> pawn_position_subscriber);

    void notify(const ApplyMoveResult &apply_move_result) override;

    [[nodiscard]] std::optional<Coordinates> getPromotionCoordinates() const;

    void resetPromotionCoordinates();
};


#endif //PROMOTIONSUBSCRIBER_H
