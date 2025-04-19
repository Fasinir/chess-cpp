#include <ostream>

#include "board/ChessBoard.h"
#include "LocalPrintTesting.h"


int main(int argc, char *argv[]) {
    std::unique_ptr<ChessBoard> chessBoard = ChessBoard::STANDARD_BOARD();
    std::cout << *chessBoard << std::endl;
    LocalPrintTesting::printMove();
    LocalPrintTesting::viewFigures();
    LocalPrintTesting::applyDefaultMove(*chessBoard);
    LocalPrintTesting::castlingOne(*chessBoard);
    LocalPrintTesting::castlingTwo(*chessBoard);
    LocalPrintTesting::castlingThree(*chessBoard);
    LocalPrintTesting::castlingFour(*chessBoard);
    LocalPrintTesting::enPassantOne(*chessBoard);
    LocalPrintTesting::enPassantTwo(*chessBoard);
    LocalPrintTesting::enPassantThree(*chessBoard);
    LocalPrintTesting::enPassantFour(*chessBoard);
    return 0;
}
