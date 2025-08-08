#ifndef PAWNPOSITIONSUBSCRIBER_H
#define PAWNPOSITIONSUBSCRIBER_H
#include <memory>
#include <unordered_set>

#include "EnPassantSubscriber.h"
#include "../../move/Coordinates.h"


class PawnPositionSubscriber : public MoveSubscriber {
    std::unordered_set<Coordinates> pawnPositions;
    std::shared_ptr<EnPassantSubscriber> enPassantSubscriber;

public:
    explicit PawnPositionSubscriber(std::shared_ptr<EnPassantSubscriber> enPassantSubscriber);

    ~PawnPositionSubscriber() override = default;

    void notify(const ApplyMoveResult &applyMoveResult) override;

    std::unordered_set<Coordinates> getPawnPositions();
};


#endif //PAWNPOSITIONSUBSCRIBER_H
