#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include "../move/Move.h"


class Subscriber {
public:
    Subscriber() = default;

    virtual ~Subscriber() = default;

    virtual void notify(Move move) = 0;
};


#endif //SUBSCRIBER_H
