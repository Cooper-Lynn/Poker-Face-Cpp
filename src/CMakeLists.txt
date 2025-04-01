cmake_minimum_required(VERSION 3.29)
project(Poker_Face_C_)

# Enable automatic handling of Qt's MOC, UIC, and RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the Qt package with Widgets component
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Include directories (for your source files)
include_directories(${CMAKE_SOURCE_DIR})

# Enable testing
include(CTest)

# Add Catch2 (if using the header-only version, no need to compile separately)
add_executable(tests PokerTests.cpp)

# Define the main executable
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
        PokerFaceView/untitled/gamebaseview.h PokerFaceView/untitled/gamebaseview.cpp PokerFaceView/untitled/gamebaseview.ui
        PokerFaceView/untitled/userinputgameinitialiser.h PokerFaceView/untitled/userinputgameinitialiser.cpp PokerFaceView/untitled/userinputgameinitialiser.ui
)

# Link Qt to the main executable
target_link_libraries(Poker_Face_C_ PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Install the executable
include(GNUInstallDirs)
install(TARGETS Poker_Face_C_
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the Qt executable if Qt 6 is used
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Poker_Face_C_)
endif()
