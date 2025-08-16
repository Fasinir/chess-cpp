#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    inline constexpr int kBoardSize = 8;

    inline constexpr std::array kRanks{1, 2, 3, 4, 5, 6, 7, 8};
    inline constexpr std::array kFiles{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    constexpr bool InBounds(const int x, const int y) noexcept {
        return x >= 0 && y >= 0 && x < kBoardSize && y < kBoardSize;
    }

    inline constexpr int kWhitePawnStartRank = 1;
    inline constexpr int kBlackPawnStartRank = 6;
    // en passant
    inline constexpr int kWhiteEnPassantTakingRank = 2;
    inline constexpr int kBlackEnPassantTakingRank = 5;
    // castling
    inline constexpr int kKingStartingFile = 4;
    inline constexpr int kKingsideCastlingFile = 6;
    inline constexpr int kKingsideCastlingRookFile = 7;
    inline constexpr int kQueensideCastlingFile = 2;
    inline constexpr int kQueensideCastlingRookFile = 0;

    // promotion
    inline constexpr int kWhitePromotionRank = 7;
    inline constexpr int kBlackPromotionRank = 0;
    inline constexpr int kFiftyMoveLimit = 50;
}


#endif // CONSTANTS_H
