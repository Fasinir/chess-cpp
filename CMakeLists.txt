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
        src/main.cpp
        src/view/MainWindow.cpp
        src/view/MainWindow.h
        src/view/MainWindow.ui
        src/controller/ChessController.cpp
        src/controller/ChessController.h
        src/view/DraggablePiece.cpp
        src/view/DraggablePiece.h
        src/model/core/Constants.h
        src/model/core/ChessBoard.cpp
        src/model/core/ChessBoard.h
        src/model/core/Field.cpp
        src/model/core/Field.h
        src/model/core/ChessBoard.h
        src/model/figures/Figure.cpp
        src/model/figures/Figure.h
        src/model/figures/King.cpp
        src/model/figures/King.h
        src/model/figures/Queen.cpp
        src/model/figures/Queen.h
        src/model/figures/Bishop.cpp
        src/model/figures/Bishop.h
        src/model/figures/Knight.cpp
        src/model/figures/Knight.h
        src/model/figures/Rook.cpp
        src/model/figures/Rook.h
        src/model/figures/Pawn.cpp
        src/model/figures/Pawn.h
        src/model/move/Coordinates.cpp
        src/model/move/Coordinates.h
        src/model/move/Move.cpp
        src/model/move/Move.h
        src/model/move/MoveType.h
        src/model/core/ChessColor.h
        src/model/move/MoveType.cpp
        src/PrintUtils.h
        src/model/move/MoveApplier.cpp
        src/model/move/MoveApplier.h
        src/model/move/ApplyMoveResult.cpp
        src/model/move/ApplyMoveResult.h
        test/LocalPrintTesting.h
        src/model/move/LegalMoveGetter.cpp
        src/model/move/LegalMoveGetter.h
        src/model/subscribers/move_subs/MoveSubscriber.h
        src/model/subscribers/move_subs/EnPassantSubscriber.cpp
        src/model/subscribers/move_subs/EnPassantSubscriber.h
        src/model/subscribers/move_subs/CastleSubscriber.cpp
        src/model/subscribers/move_subs/CastleSubscriber.h
        src/model/subscribers/move_subs/KingPositionSubscriber.cpp
        src/model/subscribers/move_subs/KingPositionSubscriber.h
        src/model/subscribers/move_subs/MoveSubscriptionManager.cpp
        src/model/subscribers/move_subs/MoveSubscriptionManager.h
        src/model/subscribers/move_subs/FiftyMoveSubscriber.cpp
        src/model/subscribers/move_subs/FiftyMoveSubscriber.h
        src/view/GameSettings.h
        src/model/move/VisionBoard.cpp
        src/model/move/VisionBoard.h
        src/model/subscribers/move_subs/PawnPositionSubscriber.cpp
        src/model/subscribers/move_subs/PawnPositionSubscriber.h
        src/model/subscribers/move_subs/PromotionSubscriber.cpp
        src/model/subscribers/move_subs/PromotionSubscriber.h
        src/view/PromotionDialog.h
        src/view/PromotionDialog.cpp
        src/view/PromotionDialog.ui
        src/model/subscribers/board_subs/ThreefoldBoardSubscriber.cpp
        src/model/subscribers/board_subs/ThreefoldBoardSubscriber.h
        src/model/core/Utils.cpp
        src/model/core/Utils.h

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
