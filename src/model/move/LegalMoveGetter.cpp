#include "LegalMoveGetter.h"

#include "VisionBoard.h"
#include "../core/Utils.h"

bool LegalMoveGetter::isWithinBounds(int x, int y) {
    return x >= 0 && y >= 0 && x < Constants::BOARD_SIZE && y < Constants::BOARD_SIZE;
}


std::vector<Move> LegalMoveGetter::generateMovesForCoordinate(const ChessBoard &chessBoard, Coordinates from,
                                                              bool skipCastle,
                                                              const std::shared_ptr<VisionBoard> &visionBoard) {
    // TODO: make it a visitor pattern?
    if (!chessBoard.figureAt(from.getX(), from.getY()).has_value())
        return {};
    std::shared_ptr<Figure> figure = chessBoard.figureAt(from.getX(), from.getY()).value();
    std::vector<Move> moves{};
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
                toAdd = handleKing(chessBoard, from, visionBoard);
                break;
            case MoveType::CASTLE:
                toAdd = skipCastle ? std::vector<Move>{} : handleCastle(chessBoard, from, visionBoard);
                break;
            default:
                throw std::invalid_argument("Illegal move type");
        }
        for (auto move: toAdd) {
            moves.emplace_back(move);
        }
    }
    return moves;
}

std::vector<Move> LegalMoveGetter::getLegalMovesForColor(ChessBoard &chessBoard, ChessColor color) {
    std::vector<Move> movesToVerify = generateMoves(chessBoard, color, false, std::make_shared<VisionBoard>());
    std::vector<Move> legalMoves;
    for (auto move: movesToVerify) {
        auto toFigureOptional = chessBoard.figureAt(move.getTo().getX(), move.getTo().getY());
        if (toFigureOptional.has_value()) {
            const auto &toFigure = toFigureOptional.value();
            if (toFigure->getColor() == color) {
                continue;
            }
        }
        std::shared_ptr applyMoveResult = moveApplier->applyMove(chessBoard, move);
        std::vector<Move> enemyMoves = generateMoves(chessBoard, Utils::oppositeColor(color), true,
                                                     std::make_shared<VisionBoard>());
        std::shared_ptr<VisionBoard> visionBoard = std::make_shared<VisionBoard>(enemyMoves);
        Coordinates kingPosition = kingPositionSubscriber->getKingCoordinates(color);
        if (move.getFrom() == kingPosition) {
            kingPosition = move.getTo();
        }
        if (!visionBoard->hasVisionOn(kingPosition)) {
            legalMoves.emplace_back(move);
        }
        moveApplier->undoMove(chessBoard, *applyMoveResult);
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

std::vector<Move> LegalMoveGetter::handlePawnEnPassant(const ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> legalMoves{};
    ChessColor color = chessBoard.figureAt(from.getX(), from.getY()).value()->getColor();
    int eligibleYCoordinate = color == ChessColor::WHITE ? 4 : 3;
    if (from.getY() == eligibleYCoordinate) {
        int toXOne = from.getX() + 1;
        int toXTwo = from.getX() - 1;
        int toY = color == ChessColor::WHITE ? from.getY() + 1 : from.getY() - 1;
        Coordinates one = Coordinates(toXOne, toY);
        if (enPassantSubscriber->canBeTakenEnPassant(one)) {
            legalMoves.emplace_back(from, one, MoveType::EN_PASSANT);
        }
        Coordinates two = Coordinates(toXTwo, toY);
        if (enPassantSubscriber->canBeTakenEnPassant(two)) {
            legalMoves.emplace_back(from, two, MoveType::EN_PASSANT);
        }
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::handlePawnTaking(const ChessBoard &chessBoard, Coordinates from) {
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
    std::vector<Move> moves{};
    int xDiff[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yDiff[] = {1, 2, 2, 1, -1, -2, -2, -1};
    std::shared_ptr<Figure> knight = chessBoard.figureAt(from.getX(), from.getY()).value();
    for (int i = 0; i < 8; i++) {
        Coordinates coordinates = Coordinates(from.getX() + xDiff[i], from.getY() + yDiff[i]);
        if (isWithinBounds(coordinates.getX(), coordinates.getY())) {
            moves.emplace_back(from, coordinates, MoveType::KNIGHT);
            moves.emplace_back(from, coordinates, MoveType::KNIGHT);
        }
    }
    return moves;
}

std::vector<Move> LegalMoveGetter::handleDiagonal(const ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> moves{};
    int xMultiple[] = {1, 1, -1, -1};
    int yMultiple[] = {1, -1, -1, 1};
    for (int i = 0; i < 4; i++) {
        int j = 1;
        int toX = from.getX() + xMultiple[i] * j;
        int toY = from.getY() + yMultiple[i] * j;
        while (j < 8
               && isWithinBounds(toX, toY)
               && !chessBoard.figureAt(toX, toY).has_value()) {
            moves.emplace_back(from, Coordinates(toX, toY), MoveType::BISHOP);
            j++;
            toX = from.getX() + xMultiple[i] * j;
            toY = from.getY() + yMultiple[i] * j;
        }
        if (isWithinBounds(toX, toY)) {
            moves.emplace_back(from, Coordinates(toX, toY), MoveType::BISHOP);
        }
    }
    return moves;
}

std::vector<Move> LegalMoveGetter::handleStraight(const ChessBoard &chessBoard, Coordinates from) {
    std::vector<Move> moves{};
    int xMultiple[] = {1, -1, 0, 0};
    int yMultiple[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int j = 1;
        int toX = from.getX() + xMultiple[i] * j;
        int toY = from.getY() + yMultiple[i] * j;
        while (j < 8
               && isWithinBounds(toX, toY)
               && !chessBoard.figureAt(toX, toY).has_value()) {
            moves.emplace_back(from, Coordinates(toX, toY), MoveType::ROOK);
            j++;
            toX = from.getX() + xMultiple[i] * j;
            toY = from.getY() + yMultiple[i] * j;
        }
        if (isWithinBounds(toX, toY)) {
            moves.emplace_back(from, Coordinates(toX, toY), MoveType::ROOK);
        }
    }
    return moves;
}

std::vector<Move> LegalMoveGetter::handleKing(const ChessBoard &chessBoard, Coordinates from,
                                              const std::shared_ptr<VisionBoard> &visionBoard) {
    std::vector<Move> moves{};
    constexpr int xDiff[] = {1, 1, 1, 0, -1, -1, -1, 0};
    constexpr int yDiff[] = {1, 0, -1, -1, -1, 0, 1, 1};
    std::shared_ptr<Figure> king = chessBoard.figureAt(from.getX(), from.getY()).value();
    for (int i = 0; i < 8; i++) {
        Coordinates coordinates = Coordinates(from.getX() + xDiff[i], from.getY() + yDiff[i]);
        if (isWithinBounds(coordinates.getX(), coordinates.getY())) {
            if (!visionBoard->hasVisionOn(coordinates)) {
                moves.emplace_back(from, coordinates, MoveType::KING);
            }
        }
    }
    return moves;
}

std::vector<Move> LegalMoveGetter::handleCastle(const ChessBoard &chessBoard, Coordinates from,
                                                const std::shared_ptr<VisionBoard> &visionBoard) {
    // A player may not castle out of, through, or into check.
    std::vector<Move> legalMoves{};
    auto castleLambda = [this, visionBoard](const ChessBoard &chessBoard, Coordinates from, int emptyStartIndex,
                                            int emptyEndIndex,
                                            int noCheckStartIndex, int noCheckEndIndex,
                                            int destinationX, int destinationY) {
        if (!castleChecker->canCastle(Coordinates(destinationX, destinationY))) {
            return false;
        }
        if (visionBoard->hasVisionOn(from)) {
            return false;
        }
        bool pathIsEmpty = true;
        for (int i = emptyStartIndex; i <= emptyEndIndex; i++) {
            Coordinates coordinates = Coordinates(i, destinationY);
            if (chessBoard.figureAt(coordinates.getX(), coordinates.getY()).has_value()) {
                pathIsEmpty = false;
                break;
            }
        }
        if (!pathIsEmpty) {
            return false;
        }
        bool willResultInCheck = false;
        for (int i = noCheckStartIndex; i <= noCheckEndIndex; i++) {
            if (visionBoard->hasVisionOn(Coordinates(i, destinationY))) {
                willResultInCheck = true;
                break;
            }
        }
        return !willResultInCheck;
    };
    // Long castle
    int destinationY = from.getY();
    if (castleLambda(chessBoard, from, from.getX() - 3, from.getX() - 1,
                     from.getX() - 2, from.getX() - 1,
                     from.getX() - 2, destinationY)) {
        legalMoves.emplace_back(from, Coordinates(from.getX() - 2, destinationY), MoveType::CASTLE);
    }
    // short castle
    if (castleLambda(chessBoard, from, from.getX() + 1, from.getX() + 2,
                     from.getX() + 1, from.getX() + 2,
                     from.getX() + 2, destinationY)) {
        legalMoves.emplace_back(from, Coordinates(from.getX() + 2, destinationY), MoveType::CASTLE);
    }
    return legalMoves;
}

std::vector<Move> LegalMoveGetter::generateMoves(const ChessBoard &chessBoard, ChessColor color, bool skipCastle,
                                                 const std::shared_ptr<VisionBoard> &visionBoard) {
    std::vector<Move> moves{};
    for (int i = 0; i < Constants::BOARD_SIZE; i++) {
        for (int j = 0; j < Constants::BOARD_SIZE; j++) {
            Coordinates coordinates = Coordinates(i, j);
            if (chessBoard.figureAt(coordinates.getX(), coordinates.getY()).has_value()) {
                std::shared_ptr<Figure> figure = chessBoard.figureAt(coordinates.getX(), coordinates.getY()).value();
                if (figure->getColor() == color) {
                    std::vector<Move> coordinateMoves = generateMovesForCoordinate(
                        chessBoard, coordinates, skipCastle, visionBoard);
                    for (auto move: coordinateMoves) {
                        moves.emplace_back(move);
                    }
                }
            }
        }
    }
    return moves;
}

bool LegalMoveGetter::hasVisionOn(const ChessBoard &chessBoard, ChessColor color, Coordinates coordinates) {
    /*std::vector<Move> moves = generateMoves(chessBoard, color, true);
    for (auto move: moves) {
        if (move.getTo() == coordinates) {
            return true;
        }
    }*/
    return false;
}

LegalMoveGetter::LegalMoveGetter() {
    this->enPassantSubscriber = std::make_unique<EnPassantSubscriber>();
    this->castleChecker = std::make_unique<CastleSubscriber>();
    this->moveApplier = std::make_unique<MoveApplier>();
    this->kingPositionSubscriber = std::make_unique<KingPositionSubscriber>();
}
