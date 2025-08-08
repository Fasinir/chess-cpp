
#include "MoveSubscriptionManager.h"

#include <iostream>

void MoveSubscriptionManager::notifySubscribers(const ApplyMoveResult &applyMoveResult) const {
    for (auto const& subscriber : entireBoardSubscribers) {
        subscriber->notify(applyMoveResult);
    }
}

void MoveSubscriptionManager::addSubscription(const std::shared_ptr<MoveSubscriber>& subscriber) {
    std::cout << "Adding subscriber" << std::endl;
    entireBoardSubscribers.emplace_back(subscriber);
}
