#ifndef CASTLECHECKER_H
#define CASTLECHECKER_H

#include <unordered_set>

#include "Subscriber.h"
#include "../move/Coordinates.h"


class CastleSubscriber : public Subscriber {
    std::unordered_set<Coordinates> availableCastles;

    void handleCastles(const Move &move, int y);

public:
    CastleSubscriber();

    ~CastleSubscriber() override = default;

    bool canCastle(Coordinates coordinates) const;

    void notify(Move move) override;
};


#endif //CASTLECHECKER_H
