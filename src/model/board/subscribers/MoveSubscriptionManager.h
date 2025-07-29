#ifndef PUBSUBMANAGERSINGLETON_H
#define PUBSUBMANAGERSINGLETON_H
#include <memory>
#include <unordered_set>

#include "Subscriber.h"
#include "../move/Move.h"

class MoveSubscriptionManager {
    std::unordered_set<std::shared_ptr<Subscriber> > entireBoardSubscribers;

public:
    MoveSubscriptionManager() = default;

    ~MoveSubscriptionManager() = default;

    void notifySubscribers(Move move);

    void removeSubscription(const std::shared_ptr<Subscriber>& subscriber);

    void addSubscription(const std::shared_ptr<Subscriber>& subscriber);
};


#endif //PUBSUBMANAGERSINGLETON_H
