#ifndef MOVEMETHOD_H
#define MOVEMETHOD_H
#include <functional>
#include <optional>

#include "../Field.h"

class MoveMethod {
    int dx;
    int dy;
    std::optional<std::function<bool(const Field &)> > optionalCondition;

public:
    MoveMethod(int dx, int dy);

    MoveMethod(int dx, int dy, const std::function<bool(const Field &)> &condition);

    ~MoveMethod() = default;

    friend std::ostream &operator<<(std::ostream &os, const MoveMethod &move);
};


#endif //MOVEMETHOD_H
