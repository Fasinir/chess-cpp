#ifndef PUBSUBMANAGERSINGLETON_H
#define PUBSUBMANAGERSINGLETON_H
#include <memory>

#include "MoveSubscriber.h"

class MoveSubscriptionManager {
    std::vector<std::shared_ptr<MoveSubscriber> > entireBoardSubscribers;

public:
    MoveSubscriptionManager() = default;

    ~MoveSubscriptionManager() = default;

    void notifySubscribers(const ApplyMoveResult &applyMoveResult) const;

    void addSubscription(const std::shared_ptr<MoveSubscriber>& subscriber);
};


#endif //PUBSUBMANAGERSINGLETON_H
