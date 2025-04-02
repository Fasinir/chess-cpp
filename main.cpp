#include <iostream>
#include <ostream>

#include "board/ChessBoard.h"

int main(int argc, char *argv[]) {
    std::unique_ptr<ChessBoard> chessBoard = ChessBoard::STANDARD_BOARD();
    std::cout << *chessBoard << std::endl;
    return 0;
}
