#include "ChessBoard.h"

#include <ostream>
#include <sstream>

#include "ConstantCoordinates.h"
#include "../figures/Bishop.h"
#include "../figures/King.h"
#include "../figures/Knight.h"
#include "../figures/Pawn.h"
#include "../figures/Queen.h"
#include "../figures/Rook.h"
#include "Coordinates.h"

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
    board->placeFigure(std::make_unique<King>(ChessColor::kBlack), ConstantCoordinates::kBlackKing);
    board->placeFigure(std::make_unique<King>(ChessColor::kWhite), ConstantCoordinates::kWhiteKing);
    // Queen
    board->placeFigure(std::make_unique<Queen>(ChessColor::kBlack), ConstantCoordinates::kBlackQueen);
    board->placeFigure(std::make_unique<Queen>(ChessColor::kWhite), ConstantCoordinates::kWhiteQueen);
    // Bishop
    board->placeFigure(std::make_unique<Bishop>(ChessColor::kBlack), ConstantCoordinates::kBlackBishopC);
    board->placeFigure(std::make_unique<Bishop>(ChessColor::kBlack), ConstantCoordinates::kBlackBishopF);
    board->placeFigure(std::make_unique<Bishop>(ChessColor::kWhite), ConstantCoordinates::kWhiteBishopC);
    board->placeFigure(std::make_unique<Bishop>(ChessColor::kWhite), ConstantCoordinates::kWhiteBishopF);
    // Knight
    board->placeFigure(std::make_unique<Knight>(ChessColor::kBlack), ConstantCoordinates::kBlackKnightB);
    board->placeFigure(std::make_unique<Knight>(ChessColor::kBlack), ConstantCoordinates::kBlackKnightG);
    board->placeFigure(std::make_unique<Knight>(ChessColor::kWhite), ConstantCoordinates::kWhiteKnightB);
    board->placeFigure(std::make_unique<Knight>(ChessColor::kWhite), ConstantCoordinates::kWhiteKnightG);
    // Rook
    board->placeFigure(std::make_unique<Rook>(ChessColor::kBlack), ConstantCoordinates::kBlackRookA);
    board->placeFigure(std::make_unique<Rook>(ChessColor::kBlack), ConstantCoordinates::kBlackRookH);
    board->placeFigure(std::make_unique<Rook>(ChessColor::kWhite), ConstantCoordinates::kWhiteRookA);
    board->placeFigure(std::make_unique<Rook>(ChessColor::kWhite), ConstantCoordinates::kWhiteRookH);

    for (int i = 0; i < Constants::kBoardSize; i++) {
        board->placeFigure(std::make_unique<Pawn>(ChessColor::kBlack), Coordinates(i, Constants::kBlackPawnStartRank));
        board->placeFigure(std::make_unique<Pawn>(ChessColor::kWhite), Coordinates(i, Constants::kWhitePawnStartRank));
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
