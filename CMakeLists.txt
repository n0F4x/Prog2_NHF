# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

# project name
project( NHF LANGUAGES CXX)

# flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -ggdb3
    -Wall -Wextra
)

# include
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/AppData
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/GUI
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/GUI/Widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/GUI/Widgets/Button
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/GUI/Widgets/Text
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Menus
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Menus/GameMenu
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Menus/InitMenu
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Menus/MainMenu
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Utilities/Math
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Utilities/STL
)

# Create target and set properties.
set(SOURCE_FILES
    ./NHF/Source/App.cpp
    ./NHF/Source/main.cpp  
    ./NHF/Source/AppData/AssetManager.cpp
    ./NHF/Source/AppData/Engine.cpp
    ./NHF/Source/AppData/MenuManager.cpp
    ./NHF/Source/AppData/Window.cpp
    ./NHF/Source/GUI/State.cpp
    ./NHF/Source/GUI/State.hpp
    ./NHF/Source/GUI/StateMachine.cpp
    ./NHF/Source/GUI/StateMachine.hpp
    ./NHF/Source/GUI/Theme.cpp
    ./NHF/Source/GUI/Widgets/Button/Button.cpp
    ./NHF/Source/GUI/Widgets/Button/ButtonState.cpp
    ./NHF/Source/GUI/Widgets/Text/Text.cpp
    ./NHF/Source/Menus/Menu.cpp
    ./NHF/Source/Menus/MenuNode.cpp
    ./NHF/Source/Menus/GameMenu/GameMenu.cpp
    ./NHF/Source/Menus/GameMenu/Physics.cpp
    ./NHF/Source/Menus/GameMenu/PlatformContainer.cpp
    ./NHF/Source/Menus/GameMenu/Platform.cpp
    ./NHF/Source/Menus/GameMenu/PreCalculator.cpp
    ./NHF/Source/Menus/GameMenu/Screen.cpp
    ./NHF/Source/Menus/GameMenu/Track.cpp
    ./NHF/Source/Menus/InitMenu/InitMenu.cpp
    ./NHF/Source/Menus/MainMenu/MainMenu.cpp
    ./NHF/Source/Utilities/Math/Angle.cpp
    ./NHF/Source/Utilities/Math/PolarVector.cpp
    ./NHF/Source/Utilities/STL/string.cpp
    ./NHF/Source/Utilities/STL/vector.cpp
)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

add_executable( NHF ${SOURCE_FILES} )

target_link_libraries(NHF sfml-graphics sfml-audio)