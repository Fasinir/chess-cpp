#ifndef LOCALPRINTTESTING_H
#define LOCALPRINTTESTING_H
#include "board/figures/Pawn.h"
#include "board/move/Coordinates.h"
#include "board/move/Move.h"
#include "ChessColor.h";
#include "board/figures/Bishop.h"
#include "board/figures/King.h"
#include "board/figures/Knight.h"
#include "board/figures/Queen.h"
#include "board/figures/Rook.h"
#include "PrintUtils.h"
#include "board/move/MoveApplier.h"

class LocalPrintTesting {
public:
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
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                chessBoard.removeFigure(i, j);
            }
        }
        chessBoard.placeFigure(std::make_unique<King>(ChessColor::WHITE), 7, 4);
        chessBoard.placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 7, 0);
        std::cout << chessBoard << std::endl;
        Coordinates coordinatesOne = Coordinates(7, 4);
        Coordinates coordinatesTwo = Coordinates(7, 2);
        Move move = Move(coordinatesOne, coordinatesTwo, MoveType::CASTLE);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void castlingTwo(ChessBoard &chessBoard) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                chessBoard.removeFigure(i, j);
            }
        }
        chessBoard.placeFigure(std::make_unique<King>(ChessColor::WHITE), 7, 4);
        chessBoard.placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 7, 7);
        std::cout << chessBoard << std::endl;
        Coordinates coordinatesOne = Coordinates(7, 4);
        Coordinates coordinatesTwo = Coordinates(7, 6);
        Move move = Move(coordinatesOne, coordinatesTwo, MoveType::CASTLE);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void castlingThree(ChessBoard &chessBoard) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                chessBoard.removeFigure(i, j);
            }
        }
        chessBoard.placeFigure(std::make_unique<King>(ChessColor::BLACK), 0, 4);
        chessBoard.placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 0, 0);
        std::cout << chessBoard << std::endl;
        Coordinates coordinatesOne = Coordinates(0, 4);
        Coordinates coordinatesTwo = Coordinates(0, 2);
        Move move = Move(coordinatesOne, coordinatesTwo, MoveType::CASTLE);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }

    static void castlingFour(ChessBoard &chessBoard) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                chessBoard.removeFigure(i, j);
            }
        }
        chessBoard.placeFigure(std::make_unique<King>(ChessColor::BLACK), 0, 4);
        chessBoard.placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 0, 7);
        std::cout << chessBoard << std::endl;
        Coordinates coordinatesOne = Coordinates(0, 4);
        Coordinates coordinatesTwo = Coordinates(0, 6);
        Move move = Move(coordinatesOne, coordinatesTwo, MoveType::CASTLE);
        MoveApplier moveApplier;
        std::unique_ptr<ApplyMoveResult> moveResult = moveApplier.applyMove(chessBoard, move);
        std::cout << chessBoard << std::endl;
        moveApplier.undoMove(chessBoard, *moveResult);
        std::cout << chessBoard << std::endl;
    }
};


#endif //LOCALPRINTTESTING_H
