#ifndef LOCALPRINTTESTING_H
#define LOCALPRINTTESTING_H
#include "board/figures/Pawn.h"
#include "board/move/Coordinates.h"
#include "board/move/Move.h"
#include "ChessColor.h"
#include "board/figures/Bishop.h"
#include "board/figures/King.h"
#include "board/figures/Knight.h"
#include "board/figures/Queen.h"
#include "board/figures/Rook.h"
#include "PrintUtils.h"
#include "board/move/LegalMoveGetter.h"
#include "board/move/MoveApplier.h"

class LocalPrintTesting {
public:
    static void clearBoard(ChessBoard &chessBoard) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                chessBoard.removeFigure(i, j);
            }
        }
    }

    static void printMove() {
        Coordinates coordinatesOne(0, 0);
        Coordinates coordinatesTwo(1, 1);
        Move move = Move(coordinatesOne, coordinatesTwo, MoveType::KING);
        std::cout << move << std::endl;
    }

    static void viewFigures() {
        Pawn pawn = Pawn(ChessColor::WHITE);
        Bishop bishop = Bishop(ChessColor::WHITE);
        Queen queen = Queen(ChessColor::WHITE);
        King king = King(ChessColor::WHITE);
        Rook rook = Rook(ChessColor::WHITE);
        Knight knight = Knight(ChessColor::WHITE);
        std::cout << pawn.getMoves() << std::endl;
        std::cout << bishop.getMoves() << std::endl;
        std::cout << queen.getMoves() << std::endl;
        std::cout << king.getMoves() << std::endl;
        std::cout << rook.getMoves() << std::endl;
        std::cout << knight.getMoves() << std::endl;
    }

    static void applyDefaultMove(ChessBoard &chessBoard) {
        // Applying random move
        Coordinates coordinatesOne = Coordinates(0, 1);
        Coordinates coordinatesTwo = Coordinates(4, 4);
        Move move = Move(coordinatesOne, coordinatesTwo, MoveType::PAWN_SINGLE_MOVE);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void castlingOne(ChessBoard &chessBoard) {
        clearBoard(chessBoard);
        chessBoard.placeFigure(std::make_unique<King>(ChessColor::BLACK), 4, 7);
        chessBoard.placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 0, 7);
        std::cout << chessBoard << std::endl;
        Coordinates coordinatesOne = Coordinates(4, 7);
        Coordinates coordinatesTwo = Coordinates(2, 7);
        Move move = Move(coordinatesOne, coordinatesTwo, MoveType::CASTLE);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void castlingTwo(ChessBoard &chessBoard) {
        clearBoard(chessBoard);
        chessBoard.placeFigure(std::make_unique<King>(ChessColor::BLACK), 4, 7);
        chessBoard.placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 7, 7);
        std::cout << chessBoard << std::endl;
        Coordinates coordinatesOne = Coordinates(4, 7);
        Coordinates coordinatesTwo = Coordinates(6, 7);
        Move move = Move(coordinatesOne, coordinatesTwo, MoveType::CASTLE);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void castlingThree(ChessBoard &chessBoard) {
        clearBoard(chessBoard);
        chessBoard.placeFigure(std::make_unique<King>(ChessColor::WHITE), 4, 0);
        chessBoard.placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 0, 0);
        std::cout << chessBoard << std::endl;
        Coordinates coordinatesOne = Coordinates(4, 0);
        Coordinates coordinatesTwo = Coordinates(2, 0);
        Move move = Move(coordinatesOne, coordinatesTwo, MoveType::CASTLE);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void castlingFour(ChessBoard &chessBoard) {
        clearBoard(chessBoard);
        chessBoard.placeFigure(std::make_unique<King>(ChessColor::WHITE), 4, 0);
        chessBoard.placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 7, 0);
        std::cout << chessBoard << std::endl;
        Coordinates coordinatesOne = Coordinates(4, 0);
        Coordinates coordinatesTwo = Coordinates(6, 0);
        Move move = Move(coordinatesOne, coordinatesTwo, MoveType::CASTLE);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void enPassantOne(ChessBoard &chessBoard) {
        clearBoard(chessBoard);
        std::shared_ptr<Figure> takingPawn = std::make_unique<Pawn>(ChessColor::WHITE);
        std::shared_ptr<Figure> takenPawn = std::make_unique<Pawn>(ChessColor::BLACK);
        chessBoard.placeFigure(takingPawn, 4, 4);
        chessBoard.placeFigure(takenPawn, 3, 4);
        std::cout << chessBoard << std::endl;
        Coordinates from = Coordinates(4, 4);
        Coordinates to = Coordinates(3, 5);
        Move move = Move(from, to, MoveType::EN_PASSANT);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void enPassantTwo(ChessBoard &chessBoard) {
        clearBoard(chessBoard);
        std::shared_ptr<Figure> takingPawn = std::make_unique<Pawn>(ChessColor::BLACK);
        std::shared_ptr<Figure> takenPawn = std::make_unique<Pawn>(ChessColor::WHITE);
        chessBoard.placeFigure(takingPawn, 4, 3);
        chessBoard.placeFigure(takenPawn, 3, 3);
        std::cout << chessBoard << std::endl;
        Coordinates from = Coordinates(4, 3);
        Coordinates to = Coordinates(3, 2);
        Move move = Move(from, to, MoveType::EN_PASSANT);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void enPassantThree(ChessBoard &chessBoard) {
        clearBoard(chessBoard);
        std::shared_ptr<Figure> takingPawn = std::make_unique<Pawn>(ChessColor::WHITE);
        std::shared_ptr<Figure> takenPawn = std::make_unique<Pawn>(ChessColor::BLACK);
        chessBoard.placeFigure(takingPawn, 4, 4);
        chessBoard.placeFigure(takenPawn, 5, 4);
        std::cout << chessBoard << std::endl;
        Coordinates from = Coordinates(4, 4);
        Coordinates to = Coordinates(5, 5);
        Move move = Move(from, to, MoveType::EN_PASSANT);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void enPassantFour(ChessBoard &chessBoard) {
        clearBoard(chessBoard);
        std::shared_ptr<Figure> takingPawn = std::make_unique<Pawn>(ChessColor::BLACK);
        std::shared_ptr<Figure> takenPawn = std::make_unique<Pawn>(ChessColor::WHITE);
        chessBoard.placeFigure(takingPawn, 4, 3);
        chessBoard.placeFigure(takenPawn, 5, 3);
        std::cout << chessBoard << std::endl;
        Coordinates from = Coordinates(4, 3);
        Coordinates to = Coordinates(5, 2);
        Move move = Move(from, to, MoveType::EN_PASSANT);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void printCoordinates() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                Coordinates coordinates = Coordinates(i, j);
                std::string algebraicNotation = coordinates.toAlgebraicNotation();
                std::cout << algebraicNotation << "->" << Coordinates::fromAlgebraicNotation(algebraicNotation) << ", ";
            }
            Coordinates coordinates = Coordinates(i, 7);
            std::string algebraicNotation = coordinates.toAlgebraicNotation();
            std::cout << algebraicNotation << "->" << Coordinates::fromAlgebraicNotation(algebraicNotation) <<
                    std::endl;
        }
    }

    static void legalMovesForStandardBoard() {
        std::unique_ptr<ChessBoard> chessBoard = ChessBoard::STANDARD_BOARD();
        std::shared_ptr enPassantChecker = std::make_unique<EnPassantChecker>();
        std::shared_ptr checkChecker = std::make_unique<CheckChecker>();
        std::shared_ptr castleChecker = std::make_unique<CastleChecker>();
        std::shared_ptr moveApplier = std::make_unique<MoveApplier>();
        LegalMoveGetter legalMoveGetter = LegalMoveGetter(enPassantChecker, checkChecker, castleChecker, moveApplier);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Coordinates coordinates = Coordinates(i, j);
                std::cout << coordinates.toAlgebraicNotation() << ": ";
                std::cout << legalMoveGetter.getLegalMovesForCoordinate(*chessBoard, coordinates) << std::endl;
            }
        }
    }

    static void legalMovesForBishop() {
        std::unique_ptr<ChessBoard> chessBoard = std::make_unique<ChessBoard>();
        std::shared_ptr enPassantChecker = std::make_unique<EnPassantChecker>();
        std::shared_ptr checkChecker = std::make_unique<CheckChecker>();
        std::shared_ptr castleChecker = std::make_unique<CastleChecker>();
        std::shared_ptr moveApplier = std::make_unique<MoveApplier>();
        LegalMoveGetter legalMoveGetter = LegalMoveGetter(enPassantChecker, checkChecker, castleChecker,
                                                          moveApplier);
        chessBoard->placeFigure(std::make_unique<Bishop>(ChessColor::WHITE), 3, 3);
        chessBoard->placeFigure(std::make_unique<Bishop>(ChessColor::WHITE), 0, 0);
        chessBoard->placeFigure(std::make_unique<Bishop>(ChessColor::BLACK), 4, 4);
        std::cout << *chessBoard << std::endl;
        std::cout << legalMoveGetter.getLegalMovesForCoordinate(*chessBoard, Coordinates(3, 3)) << std::endl;
    }

    static void legalMovesForRook() {
        std::shared_ptr legalMoveGetter = std::make_shared<LegalMoveGetter>();
        std::unique_ptr<ChessBoard> chessBoard = std::make_unique<ChessBoard>();
        chessBoard->placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 3, 3);
        chessBoard->placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 3, 6);
        chessBoard->placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 1, 3);
        std::cout << *chessBoard << std::endl;
        std::cout << legalMoveGetter->getLegalMovesForCoordinate(*chessBoard, Coordinates(3, 3)) << std::endl;
    }

    static void legalMovesForQueen() {
        std::shared_ptr legalMoveGetter = std::make_shared<LegalMoveGetter>();
        std::unique_ptr<ChessBoard> chessBoard = std::make_unique<ChessBoard>();
        chessBoard->placeFigure(std::make_unique<Queen>(ChessColor::WHITE), 3, 3);
        chessBoard->placeFigure(std::make_unique<Queen>(ChessColor::WHITE), 3, 6);
        chessBoard->placeFigure(std::make_unique<Queen>(ChessColor::BLACK), 1, 3);
        chessBoard->placeFigure(std::make_unique<Bishop>(ChessColor::WHITE), 0, 0);
        chessBoard->placeFigure(std::make_unique<Bishop>(ChessColor::BLACK), 4, 4);
        std::cout << *chessBoard << std::endl;
        std::cout << legalMoveGetter->getLegalMovesForCoordinate(*chessBoard, Coordinates(3, 3)) << std::endl;
    }

    static void legalMovesForKing() {
        std::shared_ptr legalMoveGetter = std::make_shared<LegalMoveGetter>();
        std::unique_ptr<ChessBoard> chessBoard = std::make_unique<ChessBoard>();
        chessBoard->placeFigure(std::make_unique<King>(ChessColor::WHITE), 4, 0);
        chessBoard->placeFigure(std::make_unique<Queen>(ChessColor::BLACK), 4, 1);
        chessBoard->placeFigure(std::make_unique<Pawn>(ChessColor::WHITE), 3, 0);
        chessBoard->placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 0, 0);
        chessBoard->placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 7, 0);
        std::cout << *chessBoard << std::endl;
        std::cout << legalMoveGetter->getLegalMovesForCoordinate(*chessBoard, Coordinates(4, 0)) << std::endl;
    }

    static void legalMovesForPawn() {
        std::shared_ptr enPassantChecker = std::make_unique<EnPassantChecker>();
        enPassantChecker->setEnPassantCoordinates(Coordinates(3, 5));
        std::shared_ptr checkChecker = std::make_unique<CheckChecker>();
        std::shared_ptr castleChecker = std::make_unique<CastleChecker>();
        std::shared_ptr moveApplier = std::make_unique<MoveApplier>();
        LegalMoveGetter legalMoveGetter = LegalMoveGetter(enPassantChecker, checkChecker, castleChecker,
                                                          moveApplier);
        std::unique_ptr<ChessBoard> chessBoard = std::make_unique<ChessBoard>();
        chessBoard->placeFigure(std::make_unique<Pawn>(ChessColor::WHITE), 4, 4);
        chessBoard->placeFigure(std::make_unique<Pawn>(ChessColor::BLACK), 3, 4);
        chessBoard->placeFigure(std::make_unique<Pawn>(ChessColor::BLACK), 5, 5);
        chessBoard->placeFigure(std::make_unique<Pawn>(ChessColor::WHITE), 1, 1);

        std::cout << *chessBoard << std::endl;
        std::cout << legalMoveGetter.getLegalMovesForCoordinate(*chessBoard, Coordinates(4, 4)) << std::endl;
        std::cout << legalMoveGetter.getLegalMovesForCoordinate(*chessBoard, Coordinates(1, 1)) << std::endl;
    }

    static void legalMovesForKingCastle() {
        std::shared_ptr legalMoveGetter = std::make_shared<LegalMoveGetter>();
        std::unique_ptr<ChessBoard> chessBoard = std::make_unique<ChessBoard>();
        chessBoard->placeFigure(std::make_unique<King>(ChessColor::WHITE), 4, 0);
        chessBoard->placeFigure(std::make_unique<King>(ChessColor::BLACK), 4, 7);
        chessBoard->placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 0, 0);
        chessBoard->placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 7, 0);
        chessBoard->placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 0, 7);
        chessBoard->placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 7, 7);
        std::cout << *chessBoard << std::endl;
        std::cout << legalMoveGetter->getLegalMovesForCoordinate(*chessBoard, Coordinates(4, 0)) << std::endl;
        std::cout << legalMoveGetter->getLegalMovesForCoordinate(*chessBoard, Coordinates(4, 7)) << std::endl;
    }
};


#endif //LOCALPRINTTESTING_H
