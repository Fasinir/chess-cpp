#include "CastleSubscriber.h"


void CastleSubscriber::handleCastles(const Move &move, int y) {
    // king
    if (move.getFrom() == Coordinates(4, y)) {
        available_castles_.erase(Coordinates(6, y));
        available_castles_.erase(Coordinates(2, y));
    }
    // left rook
    else if (move.getFrom() == Coordinates(0, y)
             || move.getTo() == Coordinates(0, y)) {
        available_castles_.erase(Coordinates(2, y));
    }
    // right rook
    else if (move.getFrom() == Coordinates(7, y)
             || move.getTo() == Coordinates(7, y)) {
        available_castles_.erase(Coordinates(6, y));
    }
}

CastleSubscriber::CastleSubscriber() {
    this->available_castles_ = std::unordered_set<Coordinates>();
    available_castles_.insert(Coordinates(2, 0));
    available_castles_.insert(Coordinates(6, 0));
    available_castles_.insert(Coordinates(2, 7));
    available_castles_.insert(Coordinates(6, 7));
}

bool CastleSubscriber::canCastle(const Coordinates &coordinates) const {
    return available_castles_.contains(coordinates);
}

void CastleSubscriber::notify(const ApplyMoveResult &apply_move_result) {
    // White
    handleCastles(apply_move_result.getMove(), 0);
    // Black
    handleCastles(apply_move_result.getMove(), 7);
}
