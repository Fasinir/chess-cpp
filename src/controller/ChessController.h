#pragma once

#include <memory>
#include "../model/board/ChessBoard.h"
#include "../model/board/move/MoveApplier.h"
#include "../model/board/move/LegalMoveGetter.h"
#include "../view/GameSettings.h"
#include "../model/board/subscribers/MoveSubscriptionManager.h"


class ChessController : public QObject {
    Q_OBJECT

public:
    explicit ChessController(QObject *parent = nullptr);

    void startGame(const GameSettings &settings);
    [[nodiscard]] ChessBoard *getBoard() const { return board.get(); }


public slots:
    void onPieceMoved(int fromRow, int fromCol, int toRow, int toCol);

signals:
    void illegalMoveAttempted();

    void boardUpdated(); // UI can react to this

private:
    std::unique_ptr<ChessBoard> board;
    std::unique_ptr<MoveApplier> moveApplier;
    std::unique_ptr<LegalMoveGetter> moveGetter;
    std::shared_ptr<KingPositionSubscriber> kingPositionSubscriber;
    GameSettings settings;
    std::vector<Move> currentLegalMoves;
    std::unique_ptr<MoveSubscriptionManager> manager;

    bool whiteToMove = true;


    void nextTurn();
};
