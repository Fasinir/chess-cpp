#ifndef ENPASSANTCHECKER_H
#define ENPASSANTCHECKER_H
#include <optional>
#include <unordered_set>

#include "Subscriber.h"
#include "../move/Coordinates.h"

class EnPassantSubscriber : public Subscriber {
    std::unordered_set<Coordinates> unmovedPawns;

    std::optional<Coordinates> enPassantCoordinates;

public:
    EnPassantSubscriber();

    ~EnPassantSubscriber() override = default;

    bool canBeTakenEnPassant(Coordinates coordinates) const;

    void setEnPassantCoordinates(Coordinates coordinates);

    void notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) override;
};


#endif //ENPASSANTCHECKER_H
