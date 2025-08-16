#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    inline constexpr int kBoardSize = 8;

    inline constexpr std::array kRanks{1, 2, 3, 4, 5, 6, 7, 8};
    inline constexpr std::array kFiles{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    constexpr bool InBounds(int x, int y) noexcept {
        return x >= 0 && y >= 0 && x < kBoardSize && y < kBoardSize;
    }

    inline constexpr int kWhitePawnStartRank = 1;
    inline constexpr int kBlackPawnStartRank = 6;

    inline constexpr int kDefaultTilePx = 80;
}


#endif // CONSTANTS_H
