
#include "KingPositionSubscriber.h"

Coordinates KingPositionSubscriber::getKingCoordinates(const ChessColor color) const {
    if (color == ChessColor::WHITE) {
        return whiteKingCoordinates;
    }
    return blackKingCoordinates;
}

void KingPositionSubscriber::notify(Move move) {
    //todo implement
}
