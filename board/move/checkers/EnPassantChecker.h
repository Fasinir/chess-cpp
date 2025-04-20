#ifndef ENPASSANTCHECKER_H
#define ENPASSANTCHECKER_H
#include <memory>
#include <optional>

#include "../Coordinates.h"


class EnPassantChecker {
private:
    std::optional<Coordinates> enPassantCoordinates;

public:
    EnPassantChecker() = default;

    ~EnPassantChecker() = default;

    bool canBeTakenEnPassant(Coordinates coordinates);

    void setEnPassantCoordinates(Coordinates coordinates);
};


#endif //ENPASSANTCHECKER_H
