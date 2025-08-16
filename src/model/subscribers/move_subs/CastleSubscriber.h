#ifndef CASTLECHECKER_H
#define CASTLECHECKER_H

#include <unordered_set>

#include "MoveSubscriber.h"
#include "../../core/Coordinates.h"


class CastleSubscriber final : public MoveSubscriber {
    std::unordered_set<Coordinates> available_castles_;

    void handleCastles(std::shared_ptr<Move> move, const ChessColor &color);

public:
    CastleSubscriber();

    ~CastleSubscriber() override = default;

    bool canCastle(const Coordinates &coordinates) const;

    void notify(const ApplyMoveResult &apply_move_result) override;
};


#endif //CASTLECHECKER_H
