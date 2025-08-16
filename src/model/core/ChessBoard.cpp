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
    board->placeFigure(std::make_unique<King>(ChessColor::kBlack), Coordinates(4, 7));
    board->placeFigure(std::make_unique<King>(ChessColor::kWhite), Coordinates(4, 0));
    // Queen
    board->placeFigure(std::make_unique<Queen>(ChessColor::kBlack), Coordinates(3, 7));
    board->placeFigure(std::make_unique<Queen>(ChessColor::kWhite), Coordinates(3, 0));
    // Bishop
    board->placeFigure(std::make_unique<Bishop>(ChessColor::kBlack), Coordinates(2, 7));
    board->placeFigure(std::make_unique<Bishop>(ChessColor::kBlack), Coordinates(5, 7));
    board->placeFigure(std::make_unique<Bishop>(ChessColor::kWhite), Coordinates(2, 0));
    board->placeFigure(std::make_unique<Bishop>(ChessColor::kWhite), Coordinates(5, 0));
    // Knight
    board->placeFigure(std::make_unique<Knight>(ChessColor::kBlack), Coordinates(1, 7));
    board->placeFigure(std::make_unique<Knight>(ChessColor::kBlack), Coordinates(6, 7));
    board->placeFigure(std::make_unique<Knight>(ChessColor::kWhite), Coordinates(1, 0));
    board->placeFigure(std::make_unique<Knight>(ChessColor::kWhite), Coordinates(6, 0));
    // Rook
    board->placeFigure(std::make_unique<Rook>(ChessColor::kBlack), Coordinates(0, 7));
    board->placeFigure(std::make_unique<Rook>(ChessColor::kBlack), Coordinates(7, 7));
    board->placeFigure(std::make_unique<Rook>(ChessColor::kWhite), Coordinates(0, 0));
    board->placeFigure(std::make_unique<Rook>(ChessColor::kWhite), Coordinates(7, 0));

    for (int i = 0; i < Constants::kBoardSize; i++) {
        board->placeFigure(std::make_unique<Pawn>(ChessColor::kBlack), Coordinates(i, 6));
        board->placeFigure(std::make_unique<Pawn>(ChessColor::kWhite), Coordinates(i, 1));
    }

    return board;
}

std::optional<std::shared_ptr<Figure> >
ChessBoard::placeFigure(const std::shared_ptr<Figure> &figure, const Coordinates &coordinates) {
    return this->board_.at(coordinates.getX()).at(coordinates.getY()).placeFigure(figure);
}

std::optional<std::shared_ptr<Figure> > ChessBoard::figureAt(const Coordinates &coordinates) const {
    return board_.at(coordinates.getX()).at(coordinates.getY()).getFigure();
}

void ChessBoard::removeFigure(const Coordinates &coordinates) {
    board_.at(coordinates.getX()).at(coordinates.getY()).removeFigure();
}

std::string ChessBoard::toFENBoardPart() const {
    std::ostringstream fen;

    for (int rank = Constants::kBoardSize - 1; rank >= 0; --rank) {
        int empty_count = 0;

        for (int file = 0; file < Constants::kBoardSize; ++file) {
            auto fig_opt = board_[file][rank].getFigure();
            if (!fig_opt.has_value()) {
                empty_count++;
            } else {
                if (empty_count > 0) {
                    fen << empty_count;
                    empty_count = 0;
                }
                auto fig = fig_opt.value();
                fen << fig->getSymbol();
            }
        }
        if (empty_count > 0)
            fen << empty_count;
        if (rank > 0)
            fen << '/';
    }

    return fen.str();
}
