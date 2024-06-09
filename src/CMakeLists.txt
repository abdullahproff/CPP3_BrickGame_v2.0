cmake_minimum_required(VERSION 3.23)
project(CPP3_BrickGame_v2_0_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


if(DEFINED ENV{QTDIR})
    set(CMAKE_PREFIX_PATH "$ENV{QTDIR}")
endif()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(src/brick_game/snake)
include_directories(src/brick_game/tetris)
include_directories(src/brick_game/common)
include_directories(src/controller)
include_directories(src/gui/console)
include_directories(src/gui/desktop)
include_directories(src/gui/console/common)
include_directories(src/gui/console/snake)
include_directories(src/gui/console/tetris)



add_executable(consoleBrickGame
        src/brick_game/snake/SnakeModel.cc
        src/brick_game/snake/SnakeModel.h
        src/brick_game/tetris/TetrisModel.cc
        src/brick_game/tetris/TetrisModel.h
        src/brick_game/tetris/Tetromino.h
        src/controller/SnakeController.h
        src/controller/TetrisController.h
        src/gui/console/snake/SnakeConsoleView.h
        src/gui/console/snake/SnakeConsoleView.cc
        src/gui/console/common/BrickGameConsoleView.cc
        src/gui/console/common/BrickGameConsoleView.h
        src/gui/console/BrickGameConsole.cc
        src/gui/console/common/BaseView.cc
        src/gui/console/common/BaseView.h
        src/brick_game/common/Constants.h
        src/gui/console/tetris/TetrisConsoleView.cc
        src/brick_game/tetris/Tetromino.cc
        src/brick_game/common/BaseModel.h
)

target_link_libraries(consoleBrickGame ncurses)


add_executable(desktopBrickGame
        src/brick_game/snake/SnakeModel.cc
        src/brick_game/snake/SnakeModel.h
        src/controller/SnakeController.h
        src/brick_game/tetris/TetrisModel.h
        src/brick_game/tetris/TetrisModel.cc
        src/brick_game/tetris/Tetromino.h
        src/brick_game/tetris/Tetromino.cc
        src/controller/TetrisController.h
        src/gui/desktop/snake/main.cc
        src/gui/desktop/snake/View.cc
        src/gui/desktop/snake/View.h
        src/brick_game/common/Constants.h
        src/brick_game/common/BaseModel.h)

target_link_libraries(desktopBrickGame
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

