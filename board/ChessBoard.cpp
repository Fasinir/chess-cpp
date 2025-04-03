#include "ChessBoard.h"

#include <ostream>

#include "figures/Bishop.h"
#include "figures/King.h"
#include "figures/Knight.h"
#include "figures/Pawn.h"
#include "figures/Queen.h"
#include "figures/Rook.h"

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

    // King
    board->placeFigure(std::make_unique<King>(ChessColor::WHITE), 7, 4);
    board->placeFigure(std::make_unique<King>(ChessColor::BLACK), 0, 4);
    // Queen
    board->placeFigure(std::make_unique<Queen>(ChessColor::WHITE), 7, 3);
    board->placeFigure(std::make_unique<Queen>(ChessColor::BLACK), 0, 3);
    // Bishop
    board->placeFigure(std::make_unique<Bishop>(ChessColor::WHITE), 7, 2);
    board->placeFigure(std::make_unique<Bishop>(ChessColor::WHITE), 7, 5);
    board->placeFigure(std::make_unique<Bishop>(ChessColor::BLACK), 0, 2);
    board->placeFigure(std::make_unique<Bishop>(ChessColor::BLACK), 0, 5);
    // Knight
    board->placeFigure(std::make_unique<Knight>(ChessColor::WHITE), 7, 1);
    board->placeFigure(std::make_unique<Knight>(ChessColor::WHITE), 7, 6);
    board->placeFigure(std::make_unique<Knight>(ChessColor::BLACK), 0, 1);
    board->placeFigure(std::make_unique<Knight>(ChessColor::BLACK), 0, 6);
    // Rook
    board->placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 7, 0);
    board->placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 7, 7);
    board->placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 0, 0);
    board->placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 0, 7);

    for (int i = 0; i < Constants::BOARD_SIZE; i++) {
        board->placeFigure(std::make_unique<Pawn>(ChessColor::WHITE), 6, i);
        board->placeFigure(std::make_unique<Pawn>(ChessColor::BLACK), 1, i);
    }

    return board;
}

void ChessBoard::placeFigure(std::unique_ptr<Figure> figure, int row, int col) {
    this->board.at(row).at(col).placeFigure(std::move(figure));
}
