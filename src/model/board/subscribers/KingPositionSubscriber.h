#ifndef KINGPOSITIONSUBSCRIBER_H
#define KINGPOSITIONSUBSCRIBER_H
#include "../move/Coordinates.h"
#include "../../ChessColor.h"


class KingPositionSubscriber {
    Coordinates whiteKingCoordinates;
    Coordinates blackKingCoordinates;

public:
    KingPositionSubscriber() : whiteKingCoordinates(4, 0), blackKingCoordinates(4, 7) {
    }

    ~KingPositionSubscriber() = default;

    [[nodiscard]] Coordinates getKingCoordinates(ChessColor color) const;
};


#endif //KINGPOSITIONSUBSCRIBER_H
