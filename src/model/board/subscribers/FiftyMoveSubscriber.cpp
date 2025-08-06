#include "FiftyMoveSubscriber.h"

#include <utility>

FiftyMoveSubscriber::FiftyMoveSubscriber(std::shared_ptr<PawnPositionSubscriber> pawnPositionSubscriber) {
    this->pawnPositionSubscriber = std::move(pawnPositionSubscriber);
    this->count = 0;
}

void FiftyMoveSubscriber::notify(const ApplyMoveResult &applyMoveResult, const ChessBoard &chessBoard) {
    if (applyMoveResult.getTakenFigure().has_value()
        || pawnPositionSubscriber->getPawnPositions().contains(applyMoveResult.getMove().getFrom())) {
        count = 0;
    } else {
        count++;
    }
}

bool FiftyMoveSubscriber::fiftyMoveRuleIsReached() const {
    return count == 50;
}
