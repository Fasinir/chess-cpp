#ifndef ENPASSANTCHECKER_H
#define ENPASSANTCHECKER_H
#include <optional>
#include <unordered_set>

#include "MoveSubscriber.h"
#include "../../move/Coordinates.h"

class EnPassantSubscriber : public MoveSubscriber {
    std::unordered_set<Coordinates> unmoved_pawns_;

    std::optional<Coordinates> en_passant_coordinates_;

public:
    EnPassantSubscriber();

    ~EnPassantSubscriber() override = default;

    bool canBeTakenEnPassant(Coordinates coordinates) const;

    void setEnPassantCoordinates(Coordinates coordinates);

    std::optional<Coordinates> getEnPassantCoordinates() const { return en_passant_coordinates_; }

    void notify(const ApplyMoveResult &applyMoveResult) override;
};


#endif //ENPASSANTCHECKER_H
