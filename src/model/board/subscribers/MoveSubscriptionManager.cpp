
#include "MoveSubscriptionManager.h"

#include <iostream>

void MoveSubscriptionManager::notifySubscribers(Move move) {
    for (auto const& subscriber : entireBoardSubscribers) {
        subscriber->notify(move);
    }
}

void MoveSubscriptionManager::removeSubscription(const std::shared_ptr<Subscriber>& subscriber) {
    std::cout << "Removing subscriber" << std::endl;
    entireBoardSubscribers.erase(subscriber);
}

void MoveSubscriptionManager::addSubscription(const std::shared_ptr<Subscriber>& subscriber) {
    std::cout << "Adding subscriber" << std::endl;
    entireBoardSubscribers.insert(subscriber);
}

