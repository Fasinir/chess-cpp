
#include "KingPositionSubscriber.h"

Coordinates KingPositionSubscriber::getKingCoordinates(const ChessColor kColor) const {
    if (kColor == ChessColor::kWhite) {
        return white_king_coordinates_;
    }
    return black_king_coordinates_;
}

void KingPositionSubscriber::notify(const ApplyMoveResult &apply_move_result) {
    if (white_king_coordinates_ == apply_move_result.getMove()->getFrom()) {
        white_king_coordinates_ = apply_move_result.getMove()->getTo();
        std::cout << "WhiteKingCoordinates: " << white_king_coordinates_ << "\n";
    }
    if (black_king_coordinates_ == apply_move_result.getMove()->getFrom()) {
        black_king_coordinates_ = apply_move_result.getMove()->getTo();
        std::cout << "BlackKingCoordinates: " << black_king_coordinates_ << "\n";
    }
}
