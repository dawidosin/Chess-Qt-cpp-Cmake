cmake_minimum_required(VERSION 3.14)

project(ChessAi LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

add_executable(ChessAi
  main.cpp

  main.cpp

  headers/chessbox.h
  headers/chessboard.h
  headers/game.h
  source/chessboard.cpp
  source/chessbox.cpp
  source/game.cpp

  headers/chesspiece.h
  source/chesspiece.cpp
  headers/king.h
  headers/queen.h
  headers/rook.h
  headers/bishop.h
  headers/knight.h
  headers/pawn.h
  source/king.cpp
  source/queen.cpp
  source/rook.cpp
  source/bishop.cpp
  source/knight.cpp
  source/pawn.cpp

  headers/globals.h
  source/globals.cpp
  resource.qrc
  headers/boardposition.h
  headers/gameview.h
  source/gameview.cpp
  headers/chessboardcopy.h
  source/chessboardcopy.cpp
  headers/movesstack.h
  source/movesstack.cpp
  headers/chessboardview.h
  source/chessboardview.cpp
  headers/pawnpromotion.h
  source/pawnpromotion.cpp
  headers/gameenddialog.h
  source/gameenddialog.cpp
  headers/movegenerator.h
  source/movegenerator.cpp
  headers/sidebarmenu.h
  source/sidebarmenu.cpp

  headers/imagemanager.h
  headers/interface.h
  source/interface.cpp
  headers/movemanager.h
  source/movemanager.cpp
  headers/king.h








)
target_link_libraries(ChessAi Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

include(GNUInstallDirs)
install(TARGETS ChessAi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
