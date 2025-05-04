cmake_minimum_required(VERSION 3.16)

add_executable(Chess main.cpp
        src/model/Constants.h
        src/model/board/ChessBoard.cpp
        src/model/board/ChessBoard.h
        src/model/board/Field.cpp
        src/model/board/Field.h
        src/model/board/ChessBoard.h
        src/model/board/figures/Figure.cpp
        src/model/board/figures/Figure.h
        src/model/board/figures/King.cpp
        src/model/board/figures/King.h
        src/model/board/figures/Queen.cpp
        src/model/board/figures/Queen.h
        src/model/board/figures/Bishop.cpp
        src/model/board/figures/Bishop.h
        src/model/board/figures/Knight.cpp
        src/model/board/figures/Knight.h
        src/model/board/figures/Rook.cpp
        src/model/board/figures/Rook.h
        src/model/board/figures/Pawn.cpp
        src/model/board/figures/Pawn.h
        src/model/board/move/Coordinates.cpp
        src/model/board/move/Coordinates.h
        src/model/board/move/Move.cpp
        src/model/board/move/Move.h
        src/model/board/move/MoveType.h
        src/model/ChessColor.h
        src/model/board/move/MoveType.cpp
        PrintUtils.h
        src/model/board/move/MoveApplier.cpp
        src/model/board/move/MoveApplier.h
        src/model/board/move/ApplyMoveResult.cpp
        src/model/board/move/ApplyMoveResult.h
        LocalPrintTesting.h
        src/model/board/move/LegalMoveGetter.cpp
        src/model/board/move/LegalMoveGetter.h
        src/model/board/move/checkers/CheckChecker.cpp
        src/model/board/move/checkers/CheckChecker.h
        src/model/board/move/checkers/EnPassantChecker.cpp
        src/model/board/move/checkers/EnPassantChecker.h
        src/model/board/move/checkers/CastleChecker.cpp
        src/model/board/move/checkers/CastleChecker.h
)

project(Chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
