#ifndef KINGPOSITIONSUBSCRIBER_H
#define KINGPOSITIONSUBSCRIBER_H
#include "Subscriber.h"
#include "../move/Coordinates.h"
#include "../../ChessColor.h"


class KingPositionSubscriber : public Subscriber {
    Coordinates whiteKingCoordinates;
    Coordinates blackKingCoordinates;

public:
    KingPositionSubscriber() : whiteKingCoordinates(4, 0), blackKingCoordinates(4, 7) {
    }

    [[nodiscard]] Coordinates getKingCoordinates(ChessColor color) const;

    void notify(Move move, const ChessBoard &chessBoard) override;
};


#endif //KINGPOSITIONSUBSCRIBER_H
