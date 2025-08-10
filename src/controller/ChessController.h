#pragma once

#include <memory>
#include "../model/core/ChessBoard.h"
#include "../model/move/MoveApplier.h"
#include "../model/move/LegalMoveGetter.h"
#include "../model/subscribers/board_subs/ThreefoldBoardSubscriber.h"
#include "../model/subscribers/move_subs/FiftyMoveSubscriber.h"
#include "../view/GameSettings.h"
#include "../model/subscribers/move_subs/MoveSubscriptionManager.h"
#include "../model/subscribers/move_subs/PromotionSubscriber.h"
#include "../model/subscribers/move_subs/KingPositionSubscriber.h"

enum class PromotionType { QUEEN, ROOK, BISHOP, KNIGHT };

class ChessController final : public QObject {
    Q_OBJECT

public:
    explicit ChessController(QObject *parent = nullptr);

    void startGame(const GameSettings &settings);
    [[nodiscard]] ChessBoard *getBoard() const { return board_.get(); }


public slots:
    void onPieceMoved(int from_row, int from_col, int to_row, int to_col);

    void promote(Coordinates coordinates, PromotionType type);

signals:
    void promotionRequested(Coordinates coordinates, ChessColor color);

    void illegalMoveAttempted();

    void boardUpdated(); // UI can react to this

private:
    std::unique_ptr<ChessBoard> board_;
    std::unique_ptr<MoveApplier> move_applier_;
    std::unique_ptr<LegalMoveGetter> move_getter_;
    std::shared_ptr<KingPositionSubscriber> king_position_subscriber_;
    std::shared_ptr<FiftyMoveSubscriber> fifty_move_subscriber_;
    std::shared_ptr<PromotionSubscriber> pawn_promotion_subscriber_;
    std::shared_ptr<ThreefoldBoardSubscriber> threefold_board_subscriber_;
    std::shared_ptr<CastleSubscriber> castle_subscriber_;
    std::shared_ptr<EnPassantSubscriber> en_passant_subscriber_;
    GameSettings game_settings_;
    std::vector<Move> current_legal_moves_;
    std::unique_ptr<MoveSubscriptionManager> move_subscription_manager_;

    bool white_to_move_ = true;


    void nextTurn();
};
