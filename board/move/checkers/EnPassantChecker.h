#ifndef ENPASSANTCHECKER_H
#define ENPASSANTCHECKER_H
#include <memory>

#include "../Coordinates.h"


class EnPassantChecker {
private:
    std::unique_ptr<Coordinates> enPassantCoordinates;

public:
    EnPassantChecker() : enPassantCoordinates(nullptr) {
    }

    ~EnPassantChecker() = default;

    bool canBeTakenEnPassant(Coordinates coordinates);
};


#endif //ENPASSANTCHECKER_H
