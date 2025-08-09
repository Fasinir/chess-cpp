
#include "KingPositionSubscriber.h"

Coordinates KingPositionSubscriber::getKingCoordinates(const ChessColor color) const {
    if (color == ChessColor::WHITE) {
        return white_king_coordinates_;
    }
    return black_king_coordinates_;
}

void KingPositionSubscriber::notify(const ApplyMoveResult &applyMoveResult) {
    if (white_king_coordinates_ == applyMoveResult.getMove().getFrom()) {
        white_king_coordinates_ = applyMoveResult.getMove().getTo();
        std::cout << "WhiteKingCoordinates: " << white_king_coordinates_ << "\n";
    }
    if (black_king_coordinates_ == applyMoveResult.getMove().getFrom()) {
        black_king_coordinates_ = applyMoveResult.getMove().getTo();
        std::cout << "BlackKingCoordinates: " << black_king_coordinates_ << "\n";
    }
}
