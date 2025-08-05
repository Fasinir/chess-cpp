#include "CastleSubscriber.h"


void CastleSubscriber::handleCastles(const Move &move, int y) {
    // king
    if (move.getFrom() == Coordinates(4, y)) {
        availableCastles.erase(Coordinates(6, y));
        availableCastles.erase(Coordinates(2, y));
    }
    // left rook
    else if (move.getFrom() == Coordinates(0, y)
             || move.getTo() == Coordinates(0, y)) {
        availableCastles.erase(Coordinates(2, y));
    }
    // right rook
    else if (move.getFrom() == Coordinates(7, y)
             || move.getTo() == Coordinates(7, y)) {
        availableCastles.erase(Coordinates(6, y));
    }
}

CastleSubscriber::CastleSubscriber() {
    this->availableCastles = std::unordered_set<Coordinates>();
    availableCastles.insert(Coordinates(2, 0));
    availableCastles.insert(Coordinates(6, 0));
    availableCastles.insert(Coordinates(2, 7));
    availableCastles.insert(Coordinates(6, 7));
}

bool CastleSubscriber::canCastle(const Coordinates coordinates) const {
    return availableCastles.contains(coordinates);
}

void CastleSubscriber::notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) {
    // White
    handleCastles(applyMoveResult.getMove(), 0);
    // Black
    handleCastles(applyMoveResult.getMove(), 7);
}
