
#include "ThreefoldBoardSubscriber.h"

bool ThreefoldBoardSubscriber::updateAndCheckThreefold(const ChessBoard &chess_board,
    const CastleSubscriber &castle_sub, const EnPassantSubscriber &en_passant_sub, bool white_to_move) {
    const std::string kFen = Utils::createFEN(chess_board, castle_sub, en_passant_sub, white_to_move);
    int &count = position_count_map_[kFen];
    count++;
    std::cout << "[Threefold] Position: " << kFen << " | Count: " << count << "\n";
    return count >= 3;
}
