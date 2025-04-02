#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>

class Constants {
public:
    static constexpr int BOARD_SIZE = 8;

    static const std::vector<int> RANKS;
    static const std::vector<char> FILES;
    enum class Color { WHITE, BLACK };
};

#endif // CONSTANTS_H
