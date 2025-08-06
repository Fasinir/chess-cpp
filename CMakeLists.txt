cmake_minimum_required(VERSION 3.16)

project(Chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Svg to the find_package line
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets SvgWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SvgWidgets)

set(PROJECT_SOURCES
        main.cpp
        src/view/MainWindow.cpp
        src/view/MainWindow.h
        src/view/MainWindow.ui
        src/controller/ChessController.cpp
        src/controller/ChessController.h
        src/view/DraggablePiece.cpp
        src/view/DraggablePiece.h
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
        src/model/board/subscribers/Subscriber.h
        src/model/board/subscribers/EnPassantSubscriber.cpp
        src/model/board/subscribers/EnPassantSubscriber.h
        src/model/board/subscribers/CastleSubscriber.cpp
        src/model/board/subscribers/CastleSubscriber.h
        src/model/board/subscribers/KingPositionSubscriber.cpp
        src/model/board/subscribers/KingPositionSubscriber.h
        src/model/board/subscribers/MoveSubscriptionManager.cpp
        src/model/board/subscribers/MoveSubscriptionManager.h
        src/model/board/subscribers/FiftyMoveSubscriber.cpp
        src/model/board/subscribers/FiftyMoveSubscriber.h
        src/view/GameSettings.h
        src/model/board/subscribers/Subscriber.cpp
        src/model/board/move/VisionBoard.cpp
        src/model/board/move/VisionBoard.h
        src/model/board/subscribers/PawnPositionSubscriber.cpp
        src/model/board/subscribers/PawnPositionSubscriber.h
        src/model/board/subscribers/PromotionSubscriber.cpp
        src/model/board/subscribers/PromotionSubscriber.h
        src/view/PromotionDialog.h
        src/view/PromotionDialog.cpp
        src/view/PromotionDialog.ui

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Chess
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Chess SHARED
                ${PROJECT_SOURCES}
        )
    else()
        add_executable(Chess
                ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link both Widgets and Svg modules
target_link_libraries(Chess PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::SvgWidgets)

# Bundle info
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Chess)
endif()
set_target_properties(Chess PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Chess
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Chess)
endif()
