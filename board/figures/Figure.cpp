//
// Created by Programming on 31.03.2025.
//

#include "Figure.h"


std::ostream &operator<<(std::ostream &os, const Figure &figure) {
    os << figure.getSymbol();
    return os;
}
