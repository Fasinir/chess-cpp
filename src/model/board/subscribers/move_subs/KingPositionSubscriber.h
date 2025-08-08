#ifndef KINGPOSITIONSUBSCRIBER_H
#define KINGPOSITIONSUBSCRIBER_H
#include "MoveSubscriber.h"
#include "../../move/Coordinates.h"
#include "../../../ChessColor.h"


class KingPositionSubscriber : public MoveSubscriber {
    Coordinates whiteKingCoordinates;
    Coordinates blackKingCoordinates;

public:
    KingPositionSubscriber() : whiteKingCoordinates(4, 0), blackKingCoordinates(4, 7) {
    }

    [[nodiscard]] Coordinates getKingCoordinates(ChessColor color) const;

    void notify(const ApplyMoveResult &applyMoveResult) override;
};


#endif //KINGPOSITIONSUBSCRIBER_H
