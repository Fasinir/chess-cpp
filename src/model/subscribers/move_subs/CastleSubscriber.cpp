#include "CastleSubscriber.h"

#include "../../core/ConstantCoordinates.h"

void CastleSubscriber::handleCastles(std::shared_ptr<Move> move, const ChessColor &color) {
    Coordinates king = color == ChessColor::kWhite ? ConstantCoordinates::kWhiteKing : ConstantCoordinates::kBlackKing;
    Coordinates left_rook = color == ChessColor::kWhite
                                ? ConstantCoordinates::kWhiteRookA
                                : ConstantCoordinates::kBlackRookA;
    Coordinates right_rook = color == ChessColor::kWhite
                                 ? ConstantCoordinates::kWhiteRookH
                                 : ConstantCoordinates::kBlackRookH;

    // king
    if (move->getFrom() == king) {
        available_castles_.erase(Coordinates(Constants::kKingsideCastlingFile, king.getY()));
        available_castles_.erase(Coordinates(Constants::kQueensideCastlingFile, king.getY()));
    }
    // left rook
    else if (move->getFrom() == left_rook
             || move->getTo() == left_rook) {
        available_castles_.erase(Coordinates(Constants::kQueensideCastlingFile, left_rook.getY()));
    }
    // right rook
    else if (move->getFrom() == right_rook
             || move->getTo() == right_rook) {
        available_castles_.erase(Coordinates(Constants::kKingsideCastlingFile, right_rook.getY()));
    }
}

CastleSubscriber::CastleSubscriber() {
    this->available_castles_ = std::unordered_set<Coordinates>();
    available_castles_.insert(ConstantCoordinates::kWhiteKingsideCoordinates);
    available_castles_.insert(ConstantCoordinates::kWhiteQueensideCoordinates);
    available_castles_.insert(ConstantCoordinates::kBlackKingsideCoordinates);
    available_castles_.insert(ConstantCoordinates::kBlackQueensideCoordinates);
}

bool CastleSubscriber::canCastle(const Coordinates &coordinates) const {
    return available_castles_.contains(coordinates);
}

void CastleSubscriber::notify(const ApplyMoveResult &apply_move_result) {
    handleCastles(apply_move_result.getMove(), ChessColor::kWhite);
    handleCastles(apply_move_result.getMove(), ChessColor::kBlack);
}
