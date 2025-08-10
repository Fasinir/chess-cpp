#include "LegalMoveGetter.h"

#include "VisionBoard.h"
#include "../core/Utils.h"

bool LegalMoveGetter::isWithinBounds(int x, int y) {
    return x >= 0 && y >= 0 && x < Constants::kBoardSize && y < Constants::kBoardSize;
}


std::vector<Move> LegalMoveGetter::generateMovesFromSquare(const ChessBoard &chess_board, const Coordinates &from,
                                                           bool skip_castle,
                                                           const std::shared_ptr<VisionBoard> &vision_board) {
    // TODO: make it a visitor pattern?
    if (!chess_board.figureAt(from.getX(), from.getY()).has_value())
        return {};
    std::shared_ptr<Figure> figure = chess_board.figureAt(from.getX(), from.getY()).value();
    std::vector<Move> moves{};
    for (auto move_type: figure->getMoveTypes()) {
        std::vector<Move> to_add;
        switch (move_type) {
            case MoveType::kPawnSingleMove:
                to_add = handlePawnSingleMove(chess_board, from);
                break;
            case MoveType::kPawnDoubleMove:
                to_add = handlePawnDoubleMove(chess_board, from);
                break;
            case MoveType::kPawnTaking:
                to_add = handlePawnTaking(chess_board, from);
                break;
            case MoveType::kEnPassant:
                to_add = handlePawnEnPassant(chess_board, from);
                break;
            case MoveType::kKnight:
                to_add = handleKnight(chess_board, from);
                break;
            case MoveType::kBishop:
                to_add = handleDiagonal(chess_board, from);
                break;
            case MoveType::kRook:
                to_add = handleStraight(chess_board, from);
                break;
            case MoveType::kKing:
                to_add = handleKing(chess_board, from, vision_board);
                break;
            case MoveType::kCastle:
                to_add = skip_castle ? std::vector<Move>{} : generateCastle(chess_board, from, vision_board);
                break;
            default:
                throw std::invalid_argument("Illegal move type");
        }
        for (auto move: to_add) {
            moves.emplace_back(move);
        }
    }
    return moves;
}

std::vector<Move> LegalMoveGetter::getLegalMovesForColor(ChessBoard &chess_board, ChessColor color) {
    std::vector<Move> moves_to_verify = generateMoves(chess_board, color, false, std::make_shared<VisionBoard>());
    std::vector<Move> legal_moves;
    for (auto move: moves_to_verify) {
        auto to_figure_optional = chess_board.figureAt(move.getTo().getX(), move.getTo().getY());
        if (to_figure_optional.has_value()) {
            const auto &to_figure = to_figure_optional.value();
            if (to_figure->getColor() == color) {
                continue;
            }
        }
        std::shared_ptr apply_move_result = move_applier_->applyMove(chess_board, move);
        std::vector<Move> enemy_moves = generateMoves(chess_board, Utils::oppositeColor(color), true,
                                                      std::make_shared<VisionBoard>());
        std::shared_ptr<VisionBoard> vision_board = std::make_shared<VisionBoard>(enemy_moves);
        Coordinates king_position = king_position_subscriber_->getKingCoordinates(color);
        if (move.getFrom() == king_position) {
            king_position = move.getTo();
        }
        if (!vision_board->attacks(king_position)) {
            legal_moves.emplace_back(move);
        }
        move_applier_->undoMove(chess_board, *apply_move_result);
    }
    return legal_moves;
}

std::vector<Move> LegalMoveGetter::handlePawnSingleMove(const ChessBoard &chess_board, const Coordinates &from) {
    std::vector<Move> legal_moves{};
    std::shared_ptr<Figure> pawn = chess_board.figureAt(from.getX(), from.getY()).value();
    int destination_x = from.getX();
    int destination_y = pawn->getColor() == ChessColor::kWhite
                            ? from.getY() + 1
                            : from.getY() - 1;
    if (isWithinBounds(destination_x, destination_y)
        && !chess_board.figureAt(destination_x, destination_y).has_value()) {
        legal_moves.emplace_back(from, Coordinates(destination_x, destination_y), MoveType::kPawnSingleMove);
    }
    return legal_moves;
}

std::vector<Move> LegalMoveGetter::handlePawnDoubleMove(const ChessBoard &chess_board, const Coordinates &from) {
    std::vector<Move> legal_moves{};
    if (from.getY() != 1 && from.getY() != 6) {
        return legal_moves;
    }
    std::shared_ptr<Figure> pawn = chess_board.figureAt(from.getX(), from.getY()).value();
    int first_x = from.getX();
    int first_y = pawn->getColor() == ChessColor::kWhite
                      ? from.getY() + 1
                      : from.getY() - 1;
    int second_x = from.getX();
    int second_y = pawn->getColor() == ChessColor::kWhite
                       ? from.getY() + 2
                       : from.getY() - 2;
    if (isWithinBounds(second_x, second_y)
        && !chess_board.figureAt(first_x, first_y).has_value()
        && !chess_board.figureAt(second_x, second_y).has_value()) {
        legal_moves.emplace_back(from, Coordinates(second_x, second_y), MoveType::kPawnDoubleMove);
    }
    return legal_moves;
}

std::vector<Move> LegalMoveGetter::handlePawnEnPassant(const ChessBoard &chess_board, const Coordinates &from) {
    std::vector<Move> legal_moves{};
    ChessColor color = chess_board.figureAt(from.getX(), from.getY()).value()->getColor();
    int eligible_y_coordinate = color == ChessColor::kWhite ? 4 : 3;
    if (from.getY() == eligible_y_coordinate) {
        int to_x_one = from.getX() + 1;
        int to_x_two = from.getX() - 1;
        int to_y = color == ChessColor::kWhite ? from.getY() + 1 : from.getY() - 1;
        Coordinates one = Coordinates(to_x_one, to_y);
        if (en_passant_subscriber_->canBeTakenEnPassant(one)) {
            legal_moves.emplace_back(from, one, MoveType::kEnPassant);
        }
        Coordinates two = Coordinates(to_x_two, to_y);
        if (en_passant_subscriber_->canBeTakenEnPassant(two)) {
            legal_moves.emplace_back(from, two, MoveType::kEnPassant);
        }
    }
    return legal_moves;
}

std::vector<Move> LegalMoveGetter::handlePawnTaking(const ChessBoard &chess_board, const Coordinates &from) {
    std::vector<Move> legal_moves{};
    std::shared_ptr<Figure> pawn = chess_board.figureAt(from.getX(), from.getY()).value();
    int destination_x_one = from.getX() + 1;
    int destination_x_two = from.getX() - 1;
    int destination_y = pawn->getColor() == ChessColor::kWhite
                            ? from.getY() + 1
                            : from.getY() - 1;
    if (isWithinBounds(destination_x_one, destination_y)
        && chess_board.figureAt(destination_x_one, destination_y).has_value()) {
        legal_moves.emplace_back(from, Coordinates(destination_x_one, destination_y), MoveType::kPawnTaking);
    }
    if (isWithinBounds(destination_x_two, destination_y)
        && chess_board.figureAt(destination_x_two, destination_y).has_value()) {
        legal_moves.emplace_back(from, Coordinates(destination_x_two, destination_y), MoveType::kPawnTaking);
    }
    return legal_moves;
}

std::vector<Move> LegalMoveGetter::handleKnight(const ChessBoard &chess_board, const Coordinates &from) {
    std::vector<Move> moves{};
    int x_diff[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int y_diff[] = {1, 2, 2, 1, -1, -2, -2, -1};
    std::shared_ptr<Figure> knight = chess_board.figureAt(from.getX(), from.getY()).value();
    for (int i = 0; i < Constants::kBoardSize; i++) {
        Coordinates coordinates = Coordinates(from.getX() + x_diff[i], from.getY() + y_diff[i]);
        if (isWithinBounds(coordinates.getX(), coordinates.getY())) {
            moves.emplace_back(from, coordinates, MoveType::kKnight);
        }
    }
    return moves;
}

std::vector<Move> LegalMoveGetter::handleDiagonal(const ChessBoard &chess_board, const Coordinates &from) {
    std::vector<Move> moves{};
    int x_multiple[] = {1, 1, -1, -1};
    int y_multiple[] = {1, -1, -1, 1};
    for (int i = 0; i < 4; i++) {
        int j = 1;
        int to_x = from.getX() + x_multiple[i] * j;
        int to_y = from.getY() + y_multiple[i] * j;
        while (j < Constants::kBoardSize
               && isWithinBounds(to_x, to_y)
               && !chess_board.figureAt(to_x, to_y).has_value()) {
            moves.emplace_back(from, Coordinates(to_x, to_y), MoveType::kBishop);
            j++;
            to_x = from.getX() + x_multiple[i] * j;
            to_y = from.getY() + y_multiple[i] * j;
        }
        if (isWithinBounds(to_x, to_y)) {
            moves.emplace_back(from, Coordinates(to_x, to_y), MoveType::kBishop);
        }
    }
    return moves;
}

std::vector<Move> LegalMoveGetter::handleStraight(const ChessBoard &chess_board, const Coordinates &from) {
    std::vector<Move> moves{};
    int x_multiple[] = {1, -1, 0, 0};
    int y_multiple[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int j = 1;
        int to_x = from.getX() + x_multiple[i] * j;
        int to_y = from.getY() + y_multiple[i] * j;
        while (j < Constants::kBoardSize
               && isWithinBounds(to_x, to_y)
               && !chess_board.figureAt(to_x, to_y).has_value()) {
            moves.emplace_back(from, Coordinates(to_x, to_y), MoveType::kRook);
            j++;
            to_x = from.getX() + x_multiple[i] * j;
            to_y = from.getY() + y_multiple[i] * j;
        }
        if (isWithinBounds(to_x, to_y)) {
            moves.emplace_back(from, Coordinates(to_x, to_y), MoveType::kRook);
        }
    }
    return moves;
}

std::vector<Move> LegalMoveGetter::handleKing(const ChessBoard &chess_board, const Coordinates &from,
                                              const std::shared_ptr<VisionBoard> &vision_board) {
    std::vector<Move> moves{};
    constexpr int kXDiff[] = {1, 1, 1, 0, -1, -1, -1, 0};
    constexpr int kYDiff[] = {1, 0, -1, -1, -1, 0, 1, 1};
    std::shared_ptr<Figure> king = chess_board.figureAt(from.getX(), from.getY()).value();
    for (int i = 0; i < Constants::kBoardSize; i++) {
        Coordinates coordinates = Coordinates(from.getX() + kXDiff[i], from.getY() + kYDiff[i]);
        if (isWithinBounds(coordinates.getX(), coordinates.getY())) {
            if (!vision_board->attacks(coordinates)) {
                moves.emplace_back(from, coordinates, MoveType::kKing);
            }
        }
    }
    return moves;
}

std::vector<Move> LegalMoveGetter::generateCastle(const ChessBoard &chess_board, const Coordinates &from,
                                                  const std::shared_ptr<VisionBoard> &vision_board) {
    // A player may not castle out of, through, or into check.
    std::vector<Move> legal_moves{};
    auto castle_lambda = [this, vision_board](const ChessBoard &board, const Coordinates &from, int empty_start_index,
                                              int empty_end_index,
                                              int no_check_start_index, int no_check_end_index,
                                              int destination_x, int destination_y) {
        if (!castle_checker_->canCastle(Coordinates(destination_x, destination_y))) {
            return false;
        }
        if (vision_board->attacks(from)) {
            return false;
        }
        bool path_is_empty = true;
        for (int i = empty_start_index; i <= empty_end_index; i++) {
            Coordinates coordinates = Coordinates(i, destination_y);
            if (board.figureAt(coordinates.getX(), coordinates.getY()).has_value()) {
                path_is_empty = false;
                break;
            }
        }
        if (!path_is_empty) {
            return false;
        }
        bool will_result_in_check = false;
        for (int i = no_check_start_index; i <= no_check_end_index; i++) {
            if (vision_board->attacks(Coordinates(i, destination_y))) {
                will_result_in_check = true;
                break;
            }
        }
        return !will_result_in_check;
    };
    // Long castle
    int destination_y = from.getY();
    if (castle_lambda(chess_board, from, from.getX() - 3, from.getX() - 1,
                      from.getX() - 2, from.getX() - 1,
                      from.getX() - 2, destination_y)) {
        legal_moves.emplace_back(from, Coordinates(from.getX() - 2, destination_y), MoveType::kCastle);
    }
    // short castle
    if (castle_lambda(chess_board, from, from.getX() + 1, from.getX() + 2,
                      from.getX() + 1, from.getX() + 2,
                      from.getX() + 2, destination_y)) {
        legal_moves.emplace_back(from, Coordinates(from.getX() + 2, destination_y), MoveType::kCastle);
    }
    return legal_moves;
}

std::vector<Move> LegalMoveGetter::generateMoves(const ChessBoard &chess_board, ChessColor color, bool skip_castle,
                                                 const std::shared_ptr<VisionBoard> &vision_board) {
    std::vector<Move> moves{};
    for (int i = 0; i < Constants::kBoardSize; i++) {
        for (int j = 0; j < Constants::kBoardSize; j++) {
            Coordinates coordinates = Coordinates(i, j);
            if (chess_board.figureAt(coordinates.getX(), coordinates.getY()).has_value()) {
                std::shared_ptr<Figure> figure = chess_board.figureAt(coordinates.getX(), coordinates.getY()).value();
                if (figure->getColor() == color) {
                    std::vector<Move> coordinate_moves = generateMovesFromSquare(
                        chess_board, coordinates, skip_castle, vision_board);
                    for (auto move: coordinate_moves) {
                        moves.emplace_back(move);
                    }
                }
            }
        }
    }
    return moves;
}

LegalMoveGetter::LegalMoveGetter() {
    this->en_passant_subscriber_ = std::make_unique<EnPassantSubscriber>();
    this->castle_checker_ = std::make_unique<CastleSubscriber>();
    this->move_applier_ = std::make_unique<MoveApplier>();
    this->king_position_subscriber_ = std::make_unique<KingPositionSubscriber>();
}
