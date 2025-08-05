#ifndef PAWNPOSITIONSUBSCRIBER_H
#define PAWNPOSITIONSUBSCRIBER_H
#include <memory>
#include <unordered_set>

#include "EnPassantSubscriber.h"
#include "../move/Coordinates.h"


class PawnPositionSubscriber : public Subscriber {
    std::unordered_set<Coordinates> pawnPositions;
    std::shared_ptr<EnPassantSubscriber> enPassantSubscriber;

public:
    explicit PawnPositionSubscriber(std::shared_ptr<EnPassantSubscriber> enPassantSubscriber);

    ~PawnPositionSubscriber() override = default;

    void notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) override;

    std::unordered_set<Coordinates> getPawnPositions();
};


#endif //PAWNPOSITIONSUBSCRIBER_H
