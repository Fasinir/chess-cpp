#ifndef KINGPOSITIONSUBSCRIBER_H
#define KINGPOSITIONSUBSCRIBER_H
#include "Subscriber.h"
#include "../move/Coordinates.h"
#include "../../ChessColor.h"


class KingPositionSubscriber : Subscriber {
    Coordinates whiteKingCoordinates;
    Coordinates blackKingCoordinates;

public:
    KingPositionSubscriber() : whiteKingCoordinates(4, 0), blackKingCoordinates(4, 7) {
    }

    ~KingPositionSubscriber() override = default;

    [[nodiscard]] Coordinates getKingCoordinates(ChessColor color) const;

    void notify(Move move) override;
};


#endif //KINGPOSITIONSUBSCRIBER_H
