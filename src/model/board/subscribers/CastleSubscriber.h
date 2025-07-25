#ifndef CASTLECHECKER_H
#define CASTLECHECKER_H
#include <vector>

#include "../move/Coordinates.h"


class CastleSubscriber {
private:
    std::vector<Coordinates> availableCastles;

public:
    bool canCastle(Coordinates coordinates);
};


#endif //CASTLECHECKER_H
