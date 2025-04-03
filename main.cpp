#include <iostream>
#include <ostream>

#include "board/ChessBoard.h"
#include "board/move/Coordinates.h"
#include "board/move/Move.h"
#include "board/move/MoveMethod.h"

int main(int argc, char *argv[]) {
    std::unique_ptr<ChessBoard> chessBoard = ChessBoard::STANDARD_BOARD();
    std::cout << *chessBoard << std::endl;
    Coordinates coordinates(0, 0);
    Coordinates coordinatesTwo(1, 1);
    Move move = Move(coordinates, coordinatesTwo);
    std::cout << move << std::endl;
    std::function<bool(const Field &)> myFunction;
    myFunction = [](const Field &field) {
        return true;
    };
    MoveMethod move_method(2, 1, myFunction);
    std::cout << move_method << std::endl;
    MoveMethod moveTwo(-2, -1);
    std::cout << moveTwo << std::endl;
    return 0;
}
