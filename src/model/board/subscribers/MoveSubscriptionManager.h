#ifndef PUBSUBMANAGERSINGLETON_H
#define PUBSUBMANAGERSINGLETON_H
#include <unordered_map>
#include <unordered_set>

#include "Subscriber.h"
#include "../move/Coordinates.h"
#include "../move/Move.h"


class MoveSubscriptionManager {
    std::unordered_map<Coordinates, std::unordered_set<Subscriber *> > subscribers;
    std::unordered_set<Subscriber *> entireBoardSubscribers;
public:
    MoveSubscriptionManager();

    ~MoveSubscriptionManager() = default;

    void notifySubscribers(Move move);

    void removeSubscription(Subscriber *subscriber, Coordinates coordinates);

    void removeSubscriptionToEntireBoard(Subscriber *subscriber);

    void addSubscription(Subscriber *subscriber, Coordinates coordinates);

    void addSubscriptionToEntireBoard(Subscriber *subscriber);
};


#endif //PUBSUBMANAGERSINGLETON_H
