#ifndef ENPASSANTCHECKER_H
#define ENPASSANTCHECKER_H
#include <optional>
#include <unordered_set>

#include "Subscriber.h"
#include "../move/Coordinates.h"


class EnPassantSubscriber : public Subscriber {
    std::unordered_set<Coordinates> unmovedPawns;

    std::optional<Coordinates> enPassantCoordinates;\

    void updateUnmovedPawns(const ChessBoard &chessBoard);

public:
    EnPassantSubscriber() = default;

    bool canBeTakenEnPassant(Coordinates coordinates);

    void setEnPassantCoordinates(Coordinates coordinates);

    void notify(Move move, const ChessBoard &chessBoard) override;
};


#endif //ENPASSANTCHECKER_H
