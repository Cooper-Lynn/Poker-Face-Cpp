cmake_minimum_required(VERSION 3.29)
project(Poker_Face_C_)

# -----------------------------------------------------------
# Set the path to static Qt installation
# This enables CMake to locate the Qt libraries in the repo (or on disk).
# -----------------------------------------------------------
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/qt-static-install")
# -----------------------------------------------------------
# Enable automatic handling for Qt’s meta-object features:
# - AUTOMOC: Processes Q_OBJECT macros.
# - AUTOUIC: Converts .ui files to header files.
# - AUTORCC: Processes resource files (.qrc).
# -----------------------------------------------------------
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# -----------------------------------------------------------
# Set C++ standard to C++17
# -----------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------
# Define static linking for Qt: this allows you to compile Qt into your executable.
# -----------------------------------------------------------
add_definitions(-DQT_STATICPLUGIN)

# -----------------------------------------------------------
# Locate Qt components. This will work for both Qt6 and Qt5.
# -----------------------------------------------------------
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# -----------------------------------------------------------
# Include current source directory
# -----------------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR})

# -----------------------------------------------------------
# Define the main executable
# -----------------------------------------------------------
add_executable(Poker_Face_C_
        PokerFace.cpp
        AIPlayer.cpp
        UserPlayer.cpp
        GameRunner.cpp
        HandReader.cpp
        AIModel.cpp
        PokerFaceView/untitled/mainwindow.ui
        PokerFaceView/untitled/mainwindow.cpp
        MainGui.cpp
        PokerFaceView/untitled/gameview.cpp
        PokerFaceView/untitled/gameview.ui
        PokerFaceView/untitled/GameBackground.qrc
        PokerFaceView/untitled/gamebaseview.h
        PokerFaceView/untitled/gamebaseview.cpp
        PokerFaceView/untitled/gamebaseview.ui
        PokerFaceView/untitled/userinputgameinitialiser.h
        PokerFaceView/untitled/userinputgameinitialiser.cpp
        PokerFaceView/untitled/userinputgameinitialiser.ui
)

# -----------------------------------------------------------
# Link the found Qt static libraries to the main executable.
# -----------------------------------------------------------
target_link_libraries(Poker_Face_C_ PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# -----------------------------------------------------------
# Installation Rules: Useful if you need to install the executable.
# -----------------------------------------------------------
include(GNUInstallDirs)
install(TARGETS Poker_Face_C_
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# -----------------------------------------------------------
# Finalize the executable for Qt 6:
# This ensures proper packaging of Qt dependencies in your static build.
# -----------------------------------------------------------
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Poker_Face_C_)
endif()

# -----------------------------------------------------------
# ========== Catch2 Unit Tests ==========
# Define the test executable. This duplicates some source files as needed.
# -----------------------------------------------------------
add_executable(tests PokerTests.cpp
        AIPlayer.cpp
        UserPlayer.cpp
        GameRunner.cpp
        HandReader.cpp
        AIModel.cpp
)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})
add_test(NAME PokerTests COMMAND tests)
