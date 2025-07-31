#include "EnPassantSubscriber.h"

void EnPassantSubscriber::updateUnmovedPawns(const ChessBoard &chessBoard) {
}

bool EnPassantSubscriber::canBeTakenEnPassant(Coordinates coordinates) {
    if (this->enPassantCoordinates.has_value()) {
        return coordinates == this->enPassantCoordinates;
    }
    return false;
}

void EnPassantSubscriber::setEnPassantCoordinates(Coordinates coordinates) {
    this->enPassantCoordinates = coordinates;
}

void EnPassantSubscriber::notify(Move move, const ChessBoard &chessBoard) {
    //todo implement
    enPassantCoordinates.reset();
    if (unmovedPawns.contains(move.getFrom())) {
        unmovedPawns.erase(move.getFrom());
        if (std::abs(move.getTo().getY() - move.getFrom().getY()) == 2) {

        }
    }
}
