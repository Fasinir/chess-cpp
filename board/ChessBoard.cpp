#include "ChessBoard.h"

#include <ostream>

#include "figures/King.h"

std::ostream &operator<<(std::ostream &os, const ChessBoard &board) {
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

std::unique_ptr<ChessBoard> ChessBoard::STANDARD_BOARD() {
    std::unique_ptr<ChessBoard> board = std::make_unique<ChessBoard>();

    // Place white king at e1 (row 0, column 4)
    board->placeFigure(std::make_unique<King>(Constants::Color::WHITE), 0, 4);

    // Place black king at e8 (row 7, column 4)
    board->placeFigure(std::make_unique<King>(Constants::Color::BLACK), 7, 4);

    return board;
}

void ChessBoard::placeFigure(std::unique_ptr<Figure> figure, int row, int col) {
    this->board.at(row).at(col).placeFigure(std::move(figure));
}
