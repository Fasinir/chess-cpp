cmake_minimum_required(VERSION 3.16)

add_executable(Chess main.cpp
        model/Constants.h
        model/board/ChessBoard.cpp
        model/board/ChessBoard.h
        model/board/Field.cpp
        model/board/Field.h
        model/board/ChessBoard.h
        model/board/figures/Figure.cpp
        model/board/figures/Figure.h
        model/board/figures/King.cpp
        model/board/figures/King.h
        model/board/figures/Queen.cpp
        model/board/figures/Queen.h
        model/board/figures/Bishop.cpp
        model/board/figures/Bishop.h
        model/board/figures/Knight.cpp
        model/board/figures/Knight.h
        model/board/figures/Rook.cpp
        model/board/figures/Rook.h
        model/board/figures/Pawn.cpp
        model/board/figures/Pawn.h
        model/board/move/Coordinates.cpp
        model/board/move/Coordinates.h
        model/board/move/Move.cpp
        model/board/move/Move.h
        model/board/move/MoveType.h
        model/ChessColor.h
        model/board/move/MoveType.cpp
        PrintUtils.h
        model/board/move/MoveApplier.cpp
        model/board/move/MoveApplier.h
        model/board/move/ApplyMoveResult.cpp
        model/board/move/ApplyMoveResult.h
        LocalPrintTesting.h
        model/board/move/LegalMoveGetter.cpp
        model/board/move/LegalMoveGetter.h
        model/board/move/checkers/CheckChecker.cpp
        model/board/move/checkers/CheckChecker.h
        model/board/move/checkers/EnPassantChecker.cpp
        model/board/move/checkers/EnPassantChecker.h
        model/board/move/checkers/CastleChecker.cpp
        model/board/move/checkers/CastleChecker.h
)

project(Chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
