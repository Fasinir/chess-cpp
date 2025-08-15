#ifndef MOVE_H
#define MOVE_H
#include "Coordinates.h"
#include "MoveType.h"
#include "../core/ChessBoard.h"

class ApplyMoveResult;

class Move : public std::enable_shared_from_this<Move>{
protected:
    Coordinates from_;
    Coordinates to_;
    std::string tag_;

public:
    Move(const Coordinates &from, const Coordinates &to, const std::string &tag) : from_(from), to_(to), tag_(tag) {
    };

    virtual ~Move() = default;

    friend std::ostream &operator<<(std::ostream &os, const Move &move);

    [[nodiscard]] Coordinates getFrom() const;

    [[nodiscard]] Coordinates getTo() const;

    [[nodiscard]] std::string getTag() const;

    virtual ApplyMoveResult apply(ChessBoard &chess_board) = 0;

    virtual void undo(ChessBoard &board, std::optional<std::shared_ptr<Figure>> optional_taken_figure) = 0;
};


#endif //MOVE_H
