#ifndef VISIONUTIL_H
#define VISIONUTIL_H

#include "../core/ChessBoard.h"


class VisionUtil {
public:
    static void rayVision(const ChessBoard &board, const Coordinates &from, int dx, int dy,
                   std::vector<Coordinates> &out);
};


#endif //VISIONUTIL_H
