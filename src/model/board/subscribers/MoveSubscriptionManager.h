#ifndef PUBSUBMANAGERSINGLETON_H
#define PUBSUBMANAGERSINGLETON_H
#include <memory>

#include "Subscriber.h"
#include "../move/Move.h"

class MoveSubscriptionManager {
    std::vector<std::shared_ptr<Subscriber> > entireBoardSubscribers;

public:
    MoveSubscriptionManager() = default;

    ~MoveSubscriptionManager() = default;

    void notifySubscribers(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) const;

    void addSubscription(const std::shared_ptr<Subscriber>& subscriber);
};


#endif //PUBSUBMANAGERSINGLETON_H
