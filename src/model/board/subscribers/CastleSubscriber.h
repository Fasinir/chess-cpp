#ifndef CASTLECHECKER_H
#define CASTLECHECKER_H
#include <vector>

#include "Subscriber.h"
#include "../move/Coordinates.h"


class CastleSubscriber : Subscriber {
    std::vector<Coordinates> availableCastles;

public:
    CastleSubscriber();

    ~CastleSubscriber() override = default;

    bool canCastle(Coordinates coordinates);

    void notify(Move move) override;
};


#endif //CASTLECHECKER_H
