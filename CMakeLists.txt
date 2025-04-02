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
        board/figures/King.h)

project(Chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
