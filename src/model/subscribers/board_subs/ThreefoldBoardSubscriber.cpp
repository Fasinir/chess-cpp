#include "ThreefoldBoardSubscriber.h"

bool ThreefoldBoardSubscriber::updateAndCheckThreefold(std::shared_ptr<ChessBoard> chess_board,
                                                       std::shared_ptr<CastleSubscriber> castle_sub,
                                                       std::shared_ptr<EnPassantSubscriber> en_passant_sub,
                                                       bool white_to_move) {
    const std::string kFen = Utils::createFEN(chess_board, castle_sub, en_passant_sub, white_to_move);
    int &count = position_count_map_[kFen];
    count++;
    std::cout << "[Threefold] Position: " << kFen << " | Count: " << count << "\n";
    return count >= 3;
}
