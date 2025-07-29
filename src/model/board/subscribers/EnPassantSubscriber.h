#ifndef ENPASSANTCHECKER_H
#define ENPASSANTCHECKER_H
#include <memory>
#include <optional>

#include "Subscriber.h"
#include "../move/Coordinates.h"


class EnPassantSubscriber : public Subscriber {

    std::optional<Coordinates> enPassantCoordinates;

public:
    EnPassantSubscriber() = default;

    bool canBeTakenEnPassant(Coordinates coordinates);

    void setEnPassantCoordinates(Coordinates coordinates);

    void notify(Move move) override;
};


#endif //ENPASSANTCHECKER_H
