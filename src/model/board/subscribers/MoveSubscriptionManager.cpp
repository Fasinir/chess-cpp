
#include "MoveSubscriptionManager.h"

#include <iostream>

void MoveSubscriptionManager::notifySubscribers(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) const {
    for (auto const& subscriber : entireBoardSubscribers) {
        subscriber->notify(applyMoveResult, chessBoard);
    }
}

void MoveSubscriptionManager::addSubscription(const std::shared_ptr<Subscriber>& subscriber) {
    std::cout << "Adding subscriber" << std::endl;
    entireBoardSubscribers.emplace_back(subscriber);
}
