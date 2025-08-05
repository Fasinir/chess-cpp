
#include "KingPositionSubscriber.h"

Coordinates KingPositionSubscriber::getKingCoordinates(const ChessColor color) const {
    if (color == ChessColor::WHITE) {
        return whiteKingCoordinates;
    }
    return blackKingCoordinates;
}

void KingPositionSubscriber::notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) {
    //todo implement
    if (whiteKingCoordinates == applyMoveResult.getMove().getFrom()) {
        whiteKingCoordinates = applyMoveResult.getMove().getTo();
        std::cout << "WhiteKingCoordinates: " << whiteKingCoordinates << "\n";
    }
    if (blackKingCoordinates == applyMoveResult.getMove().getFrom()) {
        blackKingCoordinates = applyMoveResult.getMove().getTo();
        std::cout << "BlackKingCoordinates: " << blackKingCoordinates << "\n";
    }
}
