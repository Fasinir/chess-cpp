#include "MoveMethod.h"

MoveMethod::MoveMethod(int dx, int dy) {
    this->dx = dx;
    this->dy = dy;
    this->optionalCondition = std::nullopt;
}

MoveMethod::MoveMethod(int dx, int dy, const std::function<bool(const Field &)> &condition) {
    this->dx = dx;
    this->dy = dy;
    this->optionalCondition = condition;
}

std::ostream &operator<<(std::ostream &os, const MoveMethod &move) {
    os << "dx: " << move.dx << ", dy: " << move.dy;
    if (move.optionalCondition) {
        os << ", with condition";
    }
    return os;
}
