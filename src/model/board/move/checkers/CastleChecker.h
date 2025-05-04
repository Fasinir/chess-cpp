#ifndef CASTLECHECKER_H
#define CASTLECHECKER_H
#include <vector>

#include "../Coordinates.h"


class CastleChecker {
private:
    std::vector<Coordinates> availableCastles;

public:
    bool canCastle(Coordinates coordinates);
};


#endif //CASTLECHECKER_H
