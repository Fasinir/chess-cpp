//
// Created by Programming on 31.03.2025.
//

#include "Field.h"
#include <ostream>

std::ostream &operator<<(std::ostream &os, const Field &field) {
    if (field.hasFigure()) {
        os << field.figure.get();
    } else {
        os << "_";
    }
    return os;
}

bool Field::hasFigure() const {
    return figure != nullptr;
}
