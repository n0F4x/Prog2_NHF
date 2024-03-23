# cmake version to be used
cmake_minimum_required( VERSION 3.20 )

include(FetchContent)

# project name
project( NHF LANGUAGES CXX)

# flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(
        /W3
    )
else ()
    add_compile_options(
        -ggdb3
        -Wall -Wextra
#        -fsanitize=address
    )
endif ()

#add_link_options(-fsanitize=address)

# include
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Core/AppData
    ${CMAKE_CURRENT_SOURCE_DIR}/NHF/Source/Core/Controller
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
    ./NHF/Source/Core/AppData/AssetManager.cpp
    ./NHF/Source/Core/AppData/Context.cpp
    ./NHF/Source/Core/AppData/ContextManager.cpp
    ./NHF/Source/Core/Controller/MenuNode.cpp
    ./NHF/Source/Core/Controller/PreView.cpp
    ./NHF/Source/Core/AppData.cpp
    ./NHF/Source/Core/Controller.cpp
    ./NHF/Source/Core/Window.cpp
    ./NHF/Source/GUI/Widgets/Bar.cpp
    ./NHF/Source/GUI/Widgets/Button.cpp
    ./NHF/Source/GUI/Widgets/InputField.cpp
    ./NHF/Source/GUI/Widgets/Text.cpp
    ./NHF/Source/GUI/Theme.cpp
    ./NHF/Source/Menus/GameMenu/PauseScreen.cpp
    ./NHF/Source/Menus/GameMenu/Platform.cpp
    ./NHF/Source/Menus/GameMenu/PlatformContainer.cpp
    ./NHF/Source/Menus/GameMenu/Player.cpp
    ./NHF/Source/Menus/GameMenu/PreCalculator.cpp
    ./NHF/Source/Menus/GameMenu/Track.cpp
    ./NHF/Source/Menus/GameMenu.cpp
    ./NHF/Source/Menus/MainMenu.cpp
    ./NHF/Source/Menus/Menu.cpp
    ./NHF/Source/Menus/MenuItem.cpp
    ./NHF/Source/Menus/OptionsMenu.cpp
    ./NHF/Source/Utilities/Math/Angle.cpp
    ./NHF/Source/Utilities/Math/BezierEasing.cpp
    ./NHF/Source/Utilities/Math/PolarVector.cpp
    ./NHF/Source/Utilities/Math/Transitions.cpp
    ./NHF/Source/Utilities/Math.cpp
    ./NHF/Source/App.cpp
    ./NHF/Source/main.cpp
    ./NHF/Tests/test_main.cpp
)

# SFML
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)
#find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

add_executable( NHF ${SOURCE_FILES} )

target_link_libraries(NHF sfml-graphics)
#target_link_libraries(NHF sfml-graphics sfml-audio)
