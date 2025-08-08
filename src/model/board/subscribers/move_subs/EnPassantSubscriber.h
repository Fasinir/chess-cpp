#ifndef ENPASSANTCHECKER_H
#define ENPASSANTCHECKER_H
#include <optional>
#include <unordered_set>

#include "MoveSubscriber.h"
#include "../../move/Coordinates.h"

class EnPassantSubscriber : public MoveSubscriber {
    std::unordered_set<Coordinates> unmovedPawns;

    std::optional<Coordinates> enPassantCoordinates;

public:
    EnPassantSubscriber();

    ~EnPassantSubscriber() override = default;

    bool canBeTakenEnPassant(Coordinates coordinates) const;

    void setEnPassantCoordinates(Coordinates coordinates);

    std::optional<Coordinates> getEnPassantCoordinates() const { return enPassantCoordinates; }

    void notify(const ApplyMoveResult &applyMoveResult) override;
};


#endif //ENPASSANTCHECKER_H
