#ifndef KINGPOSITIONSUBSCRIBER_H
#define KINGPOSITIONSUBSCRIBER_H
#include "MoveSubscriber.h"
#include "../../core/Coordinates.h"
#include "../../core/ChessColor.h"
#include "../../core/ConstantCoordinates.h"


class KingPositionSubscriber final : public MoveSubscriber {
    Coordinates white_king_coordinates_;
    Coordinates black_king_coordinates_;

public:
    KingPositionSubscriber() : white_king_coordinates_(ConstantCoordinates::kWhiteKing),
                               black_king_coordinates_(ConstantCoordinates::kBlackKing) {
    }

    [[nodiscard]] Coordinates getKingCoordinates(ChessColor color) const;

    void notify(const ApplyMoveResult &apply_move_result) override;
};


#endif //KINGPOSITIONSUBSCRIBER_H
