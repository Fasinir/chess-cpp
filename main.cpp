#include <ostream>

#include "board/ChessBoard.h"
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


int main(int argc, char *argv[]) {
    std::unique_ptr<ChessBoard> chessBoard = ChessBoard::STANDARD_BOARD();
    std::cout << *chessBoard << std::endl;
    Coordinates coordinates(0, 0);
    Coordinates coordinatesTwo(1, 1);
    Move move = Move(coordinates, coordinatesTwo, MoveType::KING);
    std::cout << move << std::endl;
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
    return 0;
}
