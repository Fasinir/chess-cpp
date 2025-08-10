#include "ChessBoard.h"

#include <ostream>
#include <sstream>

#include "../figures/Bishop.h"
#include "../figures/King.h"
#include "../figures/Knight.h"
#include "../figures/Pawn.h"
#include "../figures/Queen.h"
#include "../figures/Rook.h"
#include "../move/Coordinates.h"

std::ostream &operator<<(std::ostream &os, const ChessBoard &board) {
    os << "  ";
    for (int i = 0; i < board.board_.size(); i++) {
        os << "____";
    }
    os << "_" << std::endl;
    for (int i = Constants::kBoardSize - 1; i >= 0; i--) {
        os << Constants::kRanks.at(i) << " ";
        for (int j = 0; j < Constants::kBoardSize; j++) {
            os << "|_" << board.board_[j][i] << "_";
        }
        os << "|" << std::endl;
    }
    os << "   ";
    for (int i = 0; i < Constants::kFiles.size(); i++) {
        os << " " << Constants::kFiles[i] << "  ";
    }
    return os;
}

std::unique_ptr<ChessBoard> ChessBoard::makeStandardBoard() {
    auto board = std::make_unique<ChessBoard>();

    // King
    board->placeFigure(std::make_unique<King>(ChessColor::BLACK), 4, 7);
    board->placeFigure(std::make_unique<King>(ChessColor::WHITE), 4, 0);
    // Queen
    board->placeFigure(std::make_unique<Queen>(ChessColor::BLACK), 3, 7);
    board->placeFigure(std::make_unique<Queen>(ChessColor::WHITE), 3, 0);
    // Bishop
    board->placeFigure(std::make_unique<Bishop>(ChessColor::BLACK), 2, 7);
    board->placeFigure(std::make_unique<Bishop>(ChessColor::BLACK), 5, 7);
    board->placeFigure(std::make_unique<Bishop>(ChessColor::WHITE), 2, 0);
    board->placeFigure(std::make_unique<Bishop>(ChessColor::WHITE), 5, 0);
    // Knight
    board->placeFigure(std::make_unique<Knight>(ChessColor::BLACK), 1, 7);
    board->placeFigure(std::make_unique<Knight>(ChessColor::BLACK), 6, 7);
    board->placeFigure(std::make_unique<Knight>(ChessColor::WHITE), 1, 0);
    board->placeFigure(std::make_unique<Knight>(ChessColor::WHITE), 6, 0);
    // Rook
    board->placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 0, 7);
    board->placeFigure(std::make_unique<Rook>(ChessColor::BLACK), 7, 7);
    board->placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 0, 0);
    board->placeFigure(std::make_unique<Rook>(ChessColor::WHITE), 7, 0);

    for (int i = 0; i < Constants::kBoardSize; i++) {
        board->placeFigure(std::make_unique<Pawn>(ChessColor::BLACK), i, 6);
        board->placeFigure(std::make_unique<Pawn>(ChessColor::WHITE), i, 1);
    }

    return board;
}

std::optional<std::shared_ptr<Figure> >
ChessBoard::placeFigure(const std::shared_ptr<Figure> &figure, int x, int y) {
    return this->board_.at(x).at(y).placeFigure(figure);
}

std::optional<std::shared_ptr<Figure> > ChessBoard::figureAt(int x, int y) const {
    return board_.at(x).at(y).getFigure();
}

void ChessBoard::removeFigure(int x, int y) {
    board_.at(x).at(y).removeFigure();
}

std::string ChessBoard::toFENBoardPart() const {
    std::ostringstream fen;

    for (int rank = Constants::kBoardSize - 1; rank >= 0; --rank) { // 8 to 1
        int empty_count = 0;

        for (int file = 0; file < Constants::kBoardSize; ++file) { // a to h
            auto fig_opt = board_[file][rank].getFigure(); // file = x, rank = y
            if (!fig_opt.has_value()) {
                empty_count++;
            } else {
                // flush empty squares count
                if (empty_count > 0) {
                    fen << empty_count;
                    empty_count = 0;
                }

                auto fig = fig_opt.value();
                fen << fig->getSymbol();
            }
        }

        // flush remaining empties at end of rank
        if (empty_count > 0)
            fen << empty_count;

        if (rank > 0)
            fen << '/';
    }

    return fen.str();
}
