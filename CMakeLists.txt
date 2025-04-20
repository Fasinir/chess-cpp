cmake_minimum_required(VERSION 3.16)

add_executable(Chess main.cpp
        Constants.h
        board/ChessBoard.cpp
        board/ChessBoard.h
        board/Field.cpp
        board/Field.h
        board/ChessBoard.h
        board/figures/Figure.cpp
        board/figures/Figure.h
        board/figures/King.cpp
        board/figures/King.h
        board/figures/Queen.cpp
        board/figures/Queen.h
        board/figures/Bishop.cpp
        board/figures/Bishop.h
        board/figures/Knight.cpp
        board/figures/Knight.h
        board/figures/Rook.cpp
        board/figures/Rook.h
        board/figures/Pawn.cpp
        board/figures/Pawn.h
        board/move/Coordinates.cpp
        board/move/Coordinates.h
        board/move/Move.cpp
        board/move/Move.h
        board/move/MoveType.h
        ChessColor.h
        board/move/MoveType.cpp
        PrintUtils.h
        board/move/MoveApplier.cpp
        board/move/MoveApplier.h
        board/move/ApplyMoveResult.cpp
        board/move/ApplyMoveResult.h
        LocalPrintTesting.h
        board/move/LegalMoveGetter.cpp
        board/move/LegalMoveGetter.h
        board/move/checkers/CheckChecker.cpp
        board/move/checkers/CheckChecker.h
        board/move/checkers/EnPassantChecker.cpp
        board/move/checkers/EnPassantChecker.h
        board/move/checkers/CastleChecker.cpp
        board/move/checkers/CastleChecker.h
        board/move/checkers/DoubleMoveChecker.cpp
        board/move/checkers/DoubleMoveChecker.h
)

project(Chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
