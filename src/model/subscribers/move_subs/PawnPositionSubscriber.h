#ifndef PAWNPOSITIONSUBSCRIBER_H
#define PAWNPOSITIONSUBSCRIBER_H
#include <memory>
#include <unordered_set>

#include "EnPassantSubscriber.h"
#include "../../core/Coordinates.h"


class PawnPositionSubscriber final : public MoveSubscriber {
    std::unordered_set<Coordinates> pawn_positions_;
    std::shared_ptr<EnPassantSubscriber> en_passant_subscriber_;

public:
    explicit PawnPositionSubscriber(std::shared_ptr<EnPassantSubscriber> en_passant_subscriber);

    ~PawnPositionSubscriber() override = default;

    void notify(const ApplyMoveResult &apply_move_result) override;

    std::unordered_set<Coordinates> getPawnPositions();
};


#endif //PAWNPOSITIONSUBSCRIBER_H
