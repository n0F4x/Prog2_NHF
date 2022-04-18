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
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Menus
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Menus/GameMenu
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Utilities/Math
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Utilities/STL
)

# Create target and set properties.
set(SOURCE_FILES
    ./NHF/Source/AppData/AssetManager.cpp
    ./NHF/Source/AppData/InputManager.cpp
    ./NHF/Source/GUI/Widgets/Bar.cpp
    ./NHF/Source/GUI/Widgets/Button.cpp
    ./NHF/Source/GUI/Widgets/Text.cpp
    ./NHF/Source/GUI/Theme.cpp
    ./NHF/Source/GUI/Widget.cpp
    ./NHF/Source/Menus/GameMenu/Platform.cpp
    ./NHF/Source/Menus/GameMenu/PlatformContainer.cpp
    ./NHF/Source/Menus/GameMenu/PreCalculator.cpp
    ./NHF/Source/Menus/GameMenu/Track.cpp
    ./NHF/Source/Menus/GameMenu.cpp
    ./NHF/Source/Menus/InitMenu.cpp
    ./NHF/Source/Menus/MainMenu.cpp
    ./NHF/Source/Menus/Menu.cpp
    ./NHF/Source/Menus/MenuNode.cpp
    ./NHF/Source/Menus/OptionsMenu.cpp
    ./NHF/Source/Utilities/Math/Angle.cpp
    ./NHF/Source/Utilities/Math/PolarVector.cpp
    ./NHF/Source/Utilities/Math/Transitions.cpp
    ./NHF/Source/Utilities/STL/string.cpp
    ./NHF/Source/Utilities/STL/vector.cpp
    ./NHF/Source/App.cpp
    ./NHF/Source/AppData.cpp
    ./NHF/Source/Controller.cpp
    ./NHF/Source/main.cpp  
    ./NHF/Source/Window.cpp
)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

add_executable( NHF ${SOURCE_FILES} )

target_link_libraries(NHF sfml-graphics sfml-audio)
