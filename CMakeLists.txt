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
        PrintUtils.h)

project(Chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
