cmake_minimum_required(VERSION 3.29)
project(Poker_Face_C_)

# Enable automatic handling of Qt's UIC, MOC, and RCC
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

)

# Link Qt to the main executable
target_link_libraries(Poker_Face_C_ PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Conditional configuration for Qt 6 or lower versions
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(testQt
            MANUAL_FINALIZATION
            PokerFace.cpp
            AIPlayer.cpp
            UserPlayer.cpp
            GameRunner.cpp
            HandReader.cpp
            AIModel.cpp
            PokerFaceView/untitled/mainwindow.cpp
            PokerFaceView/untitled/mainwindow.ui
    )
else()
    add_executable(testQt
            PokerFace.cpp
            AIPlayer.cpp
            UserPlayer.cpp
            GameRunner.cpp
            HandReader.cpp
            AIModel.cpp
            PokerFaceView/untitled/mainwindow.cpp
            PokerFaceView/untitled/mainwindow.ui
    )
endif()

# Link Qt to the test executable
target_link_libraries(testQt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Set properties for macOS if needed
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.testQt)
endif()

# Set properties for macOS if needed
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set_target_properties(testQt PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER com.example.testQt
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            MACOSX_BUNDLE TRUE
            WIN32_EXECUTABLE TRUE
    )
else()
    set_target_properties(testQt PROPERTIES
            WIN32_EXECUTABLE TRUE
    )
endif()


# Install the executables
include(GNUInstallDirs)
install(TARGETS testQt
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the Qt executable if Qt 6 is used
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(testQt)
endif()
