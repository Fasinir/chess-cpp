#ifndef FIFTYMOVESUBSCRIBER_H
#define FIFTYMOVESUBSCRIBER_H
#include <vector>

#include "Subscriber.h"


class FiftyMoveSubscriber : public Subscriber {
    int count;
    std::vector<Coordinates> pawnCoordinates;

public:
    FiftyMoveSubscriber();

    void notify(Move move) override;
};


#endif //FIFTYMOVESUBSCRIBER_H
