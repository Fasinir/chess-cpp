#ifndef FIFTYMOVESUBSCRIBER_H
#define FIFTYMOVESUBSCRIBER_H
#include <vector>

#include "Subscriber.h"


class FiftyMoveSubscriber : Subscriber {
    int count;
    std::vector<Coordinates> pawnCoordinates;

public:
    FiftyMoveSubscriber();

    ~FiftyMoveSubscriber() override;

    void notify(Move move) override;
};


#endif //FIFTYMOVESUBSCRIBER_H
