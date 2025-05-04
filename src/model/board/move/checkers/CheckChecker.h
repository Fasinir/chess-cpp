#ifndef CHECKCHECKER_H
#define CHECKCHECKER_H
#include "../Coordinates.h"
#include "../../ChessBoard.h"


class CheckChecker {
    Coordinates whiteKingCoordinates;
    Coordinates blackKingCoordinates;

public:
    CheckChecker() : whiteKingCoordinates(-1, -1), blackKingCoordinates(-1, -1) {
    };

    ~CheckChecker() = default;

    bool isInCheck(ChessBoard &chessBoard, ChessColor color);
};


#endif //CHECKCHECKER_H
