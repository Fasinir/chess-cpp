#ifndef CONSTANTCOORDINATES_H
#define CONSTANTCOORDINATES_H
#include "Coordinates.h"
#include "../../Constants.h"

namespace ConstantCoordinates {
    // White back rank
    inline const Coordinates kWhiteRookA{0, 0};
    inline const Coordinates kWhiteKnightB{1, 0};
    inline const Coordinates kWhiteBishopC{2, 0};
    inline const Coordinates kWhiteQueen{3, 0};
    inline const Coordinates kWhiteKing{4, 0};
    inline const Coordinates kWhiteBishopF{5, 0};
    inline const Coordinates kWhiteKnightG{6, 0};
    inline const Coordinates kWhiteRookH{7, 0};

    // Black back rank
    inline const Coordinates kBlackRookA{0, 7};
    inline const Coordinates kBlackKnightB{1, 7};
    inline const Coordinates kBlackBishopC{2, 7};
    inline const Coordinates kBlackQueen{3, 7};
    inline const Coordinates kBlackKing{4, 7};
    inline const Coordinates kBlackBishopF{5, 7};
    inline const Coordinates kBlackKnightG{6, 7};
    inline const Coordinates kBlackRookH{7, 7};

    // Castling
    inline const Coordinates kWhiteKingsideCoordinates{6, 0};
    inline const Coordinates kWhiteQueensideCoordinates{2, 0};
    inline const Coordinates kBlackKingsideCoordinates{6, 7};
    inline const Coordinates kBlackQueensideCoordinates{2, 7};
}

#endif //CONSTANTCOORDINATES_H
