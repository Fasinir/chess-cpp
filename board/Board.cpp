#include "Board.h"

#include <ostream>

std::ostream &operator<<(std::ostream &os, const Board &board) {
    os << "  ";
    for (int i = 0; i < board.board.size(); i++) {
        os << "____";
    }
    os << "_" << std::endl;
    for (int i = 0; i < board.board.size(); i++) {
        os << Constants::RANKS.at(Constants::BOARD_SIZE - 1 - i) << " ";
        for (int j = 0; j < board.board[i].size(); j++) {
            os << "|_" << board.board[i][j] << "_";
        }
        os << "|" << std::endl;
    }
    os << "   ";
    for (int i = 0; i < Constants::FILES.size(); i++) {
        os << " " << Constants::FILES[i] << "  ";
    }
    return os;
}
