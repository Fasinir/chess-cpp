#ifndef PUBSUBMANAGERSINGLETON_H
#define PUBSUBMANAGERSINGLETON_H
#include <memory>

#include "MoveSubscriber.h"

class MoveSubscriptionManager {
    std::vector<std::shared_ptr<MoveSubscriber> > board_subscribers_;

public:
    MoveSubscriptionManager() = default;

    ~MoveSubscriptionManager() = default;

    void notifySubscribers(const ApplyMoveResult &apply_move_result) const;

    void addSubscriber(const std::shared_ptr<MoveSubscriber>& subscriber);
};


#endif //PUBSUBMANAGERSINGLETON_H
