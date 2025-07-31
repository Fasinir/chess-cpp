
#include "KingPositionSubscriber.h"

Coordinates KingPositionSubscriber::getKingCoordinates(const ChessColor color) const {
    if (color == ChessColor::WHITE) {
        return whiteKingCoordinates;
    }
    return blackKingCoordinates;
}

void KingPositionSubscriber::notify(Move move, const ChessBoard &chessBoard) {
    //todo implement
    if (whiteKingCoordinates == move.getFrom()) {
        whiteKingCoordinates = move.getTo();
        std::cout << "WhiteKingCoordinates: " << whiteKingCoordinates << "\n";
    }
    if (blackKingCoordinates == move.getFrom()) {
        blackKingCoordinates = move.getTo();
        std::cout << "BlackKingCoordinates: " << blackKingCoordinates << "\n";
    }
}
