
#include "ThreefoldBoardSubscriber.h"

bool ThreefoldBoardSubscriber::updateAndCheckIfThreefoldWasReached(const ChessBoard &chessBoard,
    const CastleSubscriber &castleSub, const EnPassantSubscriber &enPassantSub, bool whiteToMove) {
    const std::string fen = Utils::createFEN(chessBoard, castleSub, enPassantSub, whiteToMove);
    int &count = position_count_map_[fen];
    count++;
    std::cout << "[Threefold] Position: " << fen << " | Count: " << count << "\n";
    return count >= 3;
}
