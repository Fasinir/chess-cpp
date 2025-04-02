#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>

namespace Constants {
    constexpr int BOARD_SIZE = 8;

    const std::vector RANKS{1, 2, 3, 4, 5, 6, 7, 8};
    const std::vector FILES{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    enum class Color { WHITE, BLACK };
}


#endif // CONSTANTS_H
