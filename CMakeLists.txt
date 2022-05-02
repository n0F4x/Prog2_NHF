# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

# project name
project( NHF LANGUAGES CXX)

# flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -ggdb3
    -Wall -Wextra
)

# include
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source
)

# Create target and set properties.
set(SOURCE_FILES
    ./NHF/Source/Angle.cpp
    ./NHF/Source/App.cpp
    ./NHF/Source/AppData.cpp
    ./NHF/Source/BezierEasing.cpp
    ./NHF/Source/Controller.cpp
    ./NHF/Source/GameMenu.cpp
    ./NHF/Source/InitMenu.cpp
    ./NHF/Source/main.cpp
    ./NHF/Source/MainMenu.cpp
    ./NHF/Source/Math.cpp
    ./NHF/Source/Menu.cpp
    ./NHF/Source/MenuNode.cpp
    ./NHF/Source/OptionsMenu.cpp
    ./NHF/Source/Platform.cpp
    ./NHF/Source/PlatformContainer.cpp
    ./NHF/Source/Player.cpp
    ./NHF/Source/PolarVector.cpp
    ./NHF/Source/PreCalculator.cpp
    ./NHF/Source/Track.cpp
    ./NHF/Source/Transitions.cpp
    ./NHF/Source/Window.cpp
)

add_executable( NHF ${SOURCE_FILES} )

target_link_libraries(NHF)
