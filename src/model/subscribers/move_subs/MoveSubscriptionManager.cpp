
#include "MoveSubscriptionManager.h"

#include <iostream>

void MoveSubscriptionManager::notifySubscribers(const ApplyMoveResult &apply_move_result) const {
    for (auto const& subscriber : board_subscribers_) {
        subscriber->notify(apply_move_result);
    }
}

void MoveSubscriptionManager::addSubscriber(const std::shared_ptr<MoveSubscriber>& subscriber) {
    std::cout << "Adding subscriber" << std::endl;
    board_subscribers_.emplace_back(subscriber);
}
