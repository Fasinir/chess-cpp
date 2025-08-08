
#include "ThreefoldBoardSubscriber.h"

bool ThreefoldBoardSubscriber::updateAndCheckIfThreefoldWasReached(const ChessBoard &chessBoard,
    const CastleSubscriber &castleSub, const EnPassantSubscriber &enPassantSub, bool whiteToMove) {
    // Build the FEN (without halfmove/fullmove counters)
    const std::string fen = Utils::createFEN(chessBoard, castleSub, enPassantSub, whiteToMove);

    // Increment the occurrence count
    int &count = positionCountMap[fen];
    count++;

    // Debug log
    std::cout << "[Threefold] Position: " << fen << " | Count: " << count << "\n";

    // Check if reached 3 times
    return count >= 3;
}
