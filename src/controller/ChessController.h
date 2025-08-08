#pragma once

#include <memory>
#include "../model/board/ChessBoard.h"
#include "../model/board/move/MoveApplier.h"
#include "../model/board/move/LegalMoveGetter.h"
#include "../model/board/subscribers/board_subs/ThreefoldBoardSubscriber.h"
#include "../model/board/subscribers/move_subs/FiftyMoveSubscriber.h"
#include "../view/GameSettings.h"
#include "../model/board/subscribers/move_subs/MoveSubscriptionManager.h"
#include "../model/board/subscribers/move_subs/PromotionSubscriber.h"
#include "../model/board/subscribers/move_subs/KingPositionSubscriber.h"

enum class PromotionType { QUEEN, ROOK, BISHOP, KNIGHT };

class ChessController : public QObject {
    Q_OBJECT

public:
    explicit ChessController(QObject *parent = nullptr);

    void startGame(const GameSettings &settings);
    [[nodiscard]] ChessBoard *getBoard() const { return board.get(); }


public slots:
    void onPieceMoved(int fromRow, int fromCol, int toRow, int toCol);

    void promote(Coordinates coordinates, PromotionType type);

signals:
    void promotionRequested(Coordinates coordinates, ChessColor color);

    void illegalMoveAttempted();

    void boardUpdated(); // UI can react to this

private:
    std::unique_ptr<ChessBoard> board;
    std::unique_ptr<MoveApplier> moveApplier;
    std::unique_ptr<LegalMoveGetter> moveGetter;
    std::shared_ptr<KingPositionSubscriber> kingPositionSubscriber;
    std::shared_ptr<FiftyMoveSubscriber> fiftyMoveSubscriber;
    std::shared_ptr<PromotionSubscriber> promotionSubscriber;
    std::shared_ptr<ThreefoldBoardSubscriber> threefoldBoardSubscriber;
    std::shared_ptr<CastleSubscriber> castleSubscriber;
    std::shared_ptr<EnPassantSubscriber> enPassantSubscriber;
    GameSettings settings;
    std::vector<Move> currentLegalMoves;
    std::unique_ptr<MoveSubscriptionManager> manager;

    bool whiteToMove = true;


    void nextTurn();
};
