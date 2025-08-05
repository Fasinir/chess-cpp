#include "EnPassantSubscriber.h"

EnPassantSubscriber::EnPassantSubscriber() {
    this->enPassantCoordinates;
    this->unmovedPawns;
    for (int i = 0; i < 8; i++) {
        unmovedPawns.insert(Coordinates(i, 1));
        unmovedPawns.insert(Coordinates(i, 6));
    }
}

bool EnPassantSubscriber::canBeTakenEnPassant(const Coordinates coordinates) const {
    if (this->enPassantCoordinates.has_value()) {
        return coordinates == this->enPassantCoordinates;
    }
    return false;
}

void EnPassantSubscriber::setEnPassantCoordinates(Coordinates coordinates) {
    this->enPassantCoordinates = coordinates;
}

void EnPassantSubscriber::notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) {
    enPassantCoordinates.reset();
    Move move = applyMoveResult.getMove();
    if (unmovedPawns.contains(move.getFrom())) {
        unmovedPawns.erase(move.getFrom());
        if (std::abs(move.getTo().getY() - move.getFrom().getY()) == 2) {
            const int enPassantYCoordinate = move.getFrom().getY() == 1 ? 2 : 5;
            setEnPassantCoordinates(Coordinates(move.getFrom().getX(), enPassantYCoordinate));
            std::cout << "En Passant is possible for: " << Coordinates(move.getFrom().getX(), enPassantYCoordinate) <<
                    std::endl;
        }
    }
    if (unmovedPawns.contains(move.getTo())) {
        unmovedPawns.erase(move.getTo());
    }
}
