#ifndef ENPASSANTCHECKER_H
#define ENPASSANTCHECKER_H
#include <memory>
#include <optional>

#include "../move/Coordinates.h"


class EnPassantSubscriber {
private:
    std::optional<Coordinates> enPassantCoordinates;

public:
    EnPassantSubscriber() = default;

    ~EnPassantSubscriber() = default;

    bool canBeTakenEnPassant(Coordinates coordinates);

    void setEnPassantCoordinates(Coordinates coordinates);
};


#endif //ENPASSANTCHECKER_H
