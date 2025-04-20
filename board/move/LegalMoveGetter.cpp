#include "LegalMoveGetter.h"

bool LegalMoveGetter::isWithinBounds(int x, int y) {
    return x >= 0 && y >= 0 && x < Constants::BOARD_SIZE && y < Constants::BOARD_SIZE;
}

std::vector<Move> LegalMoveGetter::getLegalMovesForCoordinate(ChessBoard &chessBoard, Coordinates from) {
    // TODO: make it a visitor pattern?
    if (!chessBoard.figureAt(from.getX(), from.getY()).has_value())
        return {};
    std::shared_ptr<Figure> figure = chessBoard.figureAt(from.getX(), from.getY()).value();
    std::vector<Move> legalMoves{};
    for (auto moveType: figure->getMoves()) {
        std::vector<Move> toAdd;
        switch (moveType) {
            case MoveType::PAWN_SINGLE_MOVE:
                toAdd = handlePawnSingleMove(chessBoard, from);
                break;
            case MoveType::PAWN_DOUBLE_MOVE:
                toAdd = handlePawnDoubleMove(chessBoard, from);
                break;
            case MoveType::PAWN_TAKING:
                toAdd = handlePawnTaking(chessBoard, from);
                break;
            case MoveType::EN_PASSANT:
                toAdd = handlePawnEnPassant(chessBoard, from);
                break;
            case MoveType::KNIGHT:
                toAdd = handleKnight(chessBoard, from);
                break;
            case MoveType::BISHOP:
                toAdd = handleDiagonal(chessBoard, from);
                break;
            case MoveType::ROOK:
                toAdd = handleStraight(chessBoard, from);
                break;
            case MoveType::KING:
                toAdd = handleKing(chessBoard, from);
                break;
            case MoveType::CASTLE:
                toAdd = handleCastle(chessBoard, from);
                break;
            default:
                throw std::invalid_argument("Illegal move type");
        }
        for (auto move: toAdd) {
            std::unique_ptr<ApplyMoveResult> applyMoveResult = moveApplier->applyMove(chessBoard, move);
            if (!checkChecker->isInCheck(chessBoard, figure->getColor())) {
                legalMoves.emplace_back(move);
            }
            moveApplier->undoMove(chessBoard, *applyMoveResult);
        }
    }
    return legalMoves;
}


std::vector<Move> LegalMoveGetter::handlePawnSingleMove(const ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    std::shared_ptr<Figure> pawn = chessBoard.figureAt(from.getX(), from.getY()).value();
    int destinationX = from.getX();
    int destinationY = pawn->getColor() == ChessColor::WHITE
                           ? from.getY() + 1
                           : from.getY() - 1;
    if (isWithinBounds(destinationX, destinationY)
        && !chessBoard.figureAt(destinationX, destinationY).has_value()) {
        legalMoves.emplace_back(from, Coordinates(destinationX, destinationY), MoveType::PAWN_SINGLE_MOVE);
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handlePawnDoubleMove(const ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    if (from.getY() != 1 && from.getY() != 6) {
        return legalMoves;
    }
    std::shared_ptr<Figure> pawn = chessBoard.figureAt(from.getX(), from.getY()).value();
    int firstX = from.getX();
    int firstY = pawn->getColor() == ChessColor::WHITE
                     ? from.getY() + 1
                     : from.getY() - 1;
    int secondX = from.getX();
    int secondY = pawn->getColor() == ChessColor::WHITE
                      ? from.getY() + 2
                      : from.getY() - 2;
    if (isWithinBounds(secondX, secondY)
        && !chessBoard.figureAt(firstX, firstY).has_value()
        && !chessBoard.figureAt(secondX, secondY).has_value()) {
        legalMoves.emplace_back(from, Coordinates(secondX, secondY), MoveType::PAWN_DOUBLE_MOVE);
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handlePawnEnPassant(ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    ChessColor color = chessBoard.figureAt(from.getX(), from.getY()).value()->getColor();
    int eligibleYCoordinate = color == ChessColor::WHITE ? 4 : 3;
    if (from.getY() == eligibleYCoordinate) {
        int toXOne = from.getX() + 1;
        int toXTwo = from.getX() - 1;
        int toY = color == ChessColor::WHITE ? from.getY() + 1 : from.getY() - 1;
        Coordinates one = Coordinates(toXOne, toY);
        if (enPassantChecker->canBeTakenEnPassant(one)) {
            legalMoves.emplace_back(from, one, MoveType::EN_PASSANT);
        }
        Coordinates two = Coordinates(toXTwo, toY);
        if (enPassantChecker->canBeTakenEnPassant(two)) {
            legalMoves.emplace_back(from, two, MoveType::EN_PASSANT);
        }
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handlePawnTaking(ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    std::shared_ptr<Figure> pawn = chessBoard.figureAt(from.getX(), from.getY()).value();
    int destinationXOne = from.getX() + 1;
    int destinationXTwo = from.getX() - 1;
    int destinationY = pawn->getColor() == ChessColor::WHITE
                           ? from.getY() + 1
                           : from.getY() - 1;
    if (isWithinBounds(destinationXOne, destinationY)
        && chessBoard.figureAt(destinationXOne, destinationY).has_value()) {
        legalMoves.emplace_back(from, Coordinates(destinationXOne, destinationY), MoveType::PAWN_TAKING);
    }
    if (isWithinBounds(destinationXTwo, destinationY)
        && chessBoard.figureAt(destinationXTwo, destinationY).has_value()) {
        legalMoves.emplace_back(from, Coordinates(destinationXTwo, destinationY), MoveType::PAWN_TAKING);
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handleKnight(const ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    int xDiff[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yDiff[] = {1, 2, 2, 1, -1, -2, -2, -1};
    std::shared_ptr<Figure> knight = chessBoard.figureAt(from.getX(), from.getY()).value();
    for (int i = 0; i < 8; i++) {
        Coordinates coordinates = Coordinates(from.getX() + xDiff[i], from.getY() + yDiff[i]);
        if (isWithinBounds(coordinates.getX(), coordinates.getY())) {
            if (chessBoard.figureAt(coordinates.getX(), coordinates.getY()).has_value()) {
                if (const std::shared_ptr<Figure> figure = chessBoard.figureAt(coordinates.getX(), coordinates.getY()).
                        value(); figure->getColor() != knight->getColor()) {
                    legalMoves.emplace_back(from, coordinates, MoveType::KNIGHT);
                }
            } else {
                legalMoves.emplace_back(from, coordinates, MoveType::KNIGHT);
            }
        }
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handleDiagonal(const ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    ChessColor color = chessBoard.figureAt(from.getX(), from.getY()).value()->getColor();
    int xMultiple[] = {1, 1, -1, -1};
    int yMultiple[] = {1, -1, -1, 1};
    for (int i = 0; i < 4; i++) {
        int j = 1;
        int toX = from.getX() + xMultiple[i] * j;
        int toY = from.getY() + yMultiple[i] * j;
        while (j < 8
               && isWithinBounds(toX, toY)
               && !chessBoard.figureAt(toX, toY).has_value()) {
            legalMoves.emplace_back(from, Coordinates(toX, toY), MoveType::BISHOP);
            j++;
            toX = from.getX() + xMultiple[i] * j;
            toY = from.getY() + yMultiple[i] * j;
        }
        if (isWithinBounds(toX, toY)) {
            if (chessBoard.figureAt(toX, toY).value()->getColor() != color) {
                legalMoves.emplace_back(from, Coordinates(toX, toY), MoveType::BISHOP);
            }
        }
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handleStraight(const ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    ChessColor color = chessBoard.figureAt(from.getX(), from.getY()).value()->getColor();
    int xMultiple[] = {1, -1, 0, 0};
    int yMultiple[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int j = 1;
        int toX = from.getX() + xMultiple[i] * j;
        int toY = from.getY() + yMultiple[i] * j;
        while (j < 8
               && isWithinBounds(toX, toY)
               && !chessBoard.figureAt(toX, toY).has_value()) {
            legalMoves.emplace_back(from, Coordinates(toX, toY), MoveType::ROOK);
            j++;
            toX = from.getX() + xMultiple[i] * j;
            toY = from.getY() + yMultiple[i] * j;
        }
        if (isWithinBounds(toX, toY)) {
            if (chessBoard.figureAt(toX, toY).value()->getColor() != color) {
                legalMoves.emplace_back(from, Coordinates(toX, toY), MoveType::ROOK);
            }
        }
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handleKing(ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    constexpr int xDiff[] = {1, 1, 1, 0, -1, -1, -1, 0};
    constexpr int yDiff[] = {1, 0, -1, -1, -1, 0, 1, 1};
    std::shared_ptr<Figure> king = chessBoard.figureAt(from.getX(), from.getY()).value();
    for (int i = 0; i < 8; i++) {
        Coordinates coordinates = Coordinates(from.getX() + xDiff[i], from.getY() + yDiff[i]);
        if (isWithinBounds(coordinates.getX(), coordinates.getY())) {
            if (chessBoard.figureAt(coordinates.getX(), coordinates.getY()).has_value()) {
                if (const std::shared_ptr<Figure> figure = chessBoard.figureAt(coordinates.getX(), coordinates.getY()).
                        value(); figure->getColor() != king->getColor()) {
                    legalMoves.emplace_back(from, coordinates, MoveType::KING);
                }
            } else {
                legalMoves.emplace_back(from, coordinates, MoveType::KING);
            }
        }
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handleCastle(ChessBoard &chessBoard, Coordinates from) {
    // A player may not castle out of, through, or into check.
    std::vector<Move> legalMoves{};
    ChessColor color = chessBoard.figureAt(from.getX(), from.getY()).value()->getColor();
    // Long castle
    int destinationY = from.getY();
    int destinationXLong = from.getX() - 2;
    if (castleChecker->canCastle(Coordinates(destinationXLong, destinationY))) {
        bool pathIsEmpty = true;
        for (int i = 1; i < from.getX(); i++) {
            Coordinates coordinates = Coordinates(i, destinationY);
            if (chessBoard.figureAt(coordinates.getX(), coordinates.getY()).has_value()) {
                pathIsEmpty = false;
            }
        }
        bool willResultInCheck = false;
        if (pathIsEmpty) {
            for (int i = destinationXLong; i < from.getX(); i++) {
                Move move = Move(from, Coordinates(i, destinationY), MoveType::KING);
                std::shared_ptr applyMoveResult = moveApplier->applyMove(chessBoard, move);
                if (checkChecker->isInCheck(chessBoard, color)) {
                    willResultInCheck = true;
                }
                moveApplier->undoMove(chessBoard, *applyMoveResult);
            }
        }
        if (pathIsEmpty && !willResultInCheck) {
            legalMoves.emplace_back(from, Coordinates(destinationXLong, destinationY), MoveType::CASTLE);
        }
    }
    // short castle
    int destinationXShort = from.getX() + 2;
    if (castleChecker->canCastle(Coordinates(destinationXLong, destinationY))) {
        bool pathIsEmpty = true;
        for (int i = destinationXShort; i > from.getX(); i--) {
            Coordinates coordinates = Coordinates(i, destinationY);
            if (chessBoard.figureAt(coordinates.getX(), coordinates.getY()).has_value()) {
                pathIsEmpty = false;
            }
        }
        bool willResultInCheck = false;
        if (pathIsEmpty) {
            for (int i = destinationXShort; i > from.getX(); i--) {
                Move move = Move(from, Coordinates(i, destinationY), MoveType::KING);
                std::shared_ptr applyMoveResult = moveApplier->applyMove(chessBoard, move);
                if (checkChecker->isInCheck(chessBoard, color)) {
                    willResultInCheck = true;
                }
                moveApplier->undoMove(chessBoard, *applyMoveResult);
            }
        }
        if (pathIsEmpty && !willResultInCheck) {
            legalMoves.emplace_back(from, Coordinates(destinationXLong, destinationY), MoveType::CASTLE);
        }
    }
    return legalMoves;
}

LegalMoveGetter::LegalMoveGetter() {
    this->enPassantChecker = std::make_unique<EnPassantChecker>();
    this->checkChecker = std::make_unique<CheckChecker>();
    this->castleChecker = std::make_unique<CastleChecker>();
    this->moveApplier = std::make_unique<MoveApplier>();
}
