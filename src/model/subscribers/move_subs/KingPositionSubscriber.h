#ifndef KINGPOSITIONSUBSCRIBER_H
#define KINGPOSITIONSUBSCRIBER_H
#include "MoveSubscriber.h"
#include "../../move/Coordinates.h"
#include "../../core/ChessColor.h"


class KingPositionSubscriber final : public MoveSubscriber {
    Coordinates white_king_coordinates_;
    Coordinates black_king_coordinates_;

public:
    KingPositionSubscriber() : white_king_coordinates_(4, 0), black_king_coordinates_(4, 7) {
    }

    [[nodiscard]] Coordinates getKingCoordinates(ChessColor color) const;

    void notify(const ApplyMoveResult &apply_move_result) override;
};


#endif //KINGPOSITIONSUBSCRIBER_H
