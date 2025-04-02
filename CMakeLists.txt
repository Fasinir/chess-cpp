cmake_minimum_required(VERSION 3.16)

add_executable(Chess main.cpp
        Constants.h
        Constants.cpp
        board/Board.cpp
        board/Board.h
        board/Field.cpp
        board/Field.h
        board/Board.h
        board/figures/Figure.cpp
        board/figures/Figure.h)

project(Chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
