cmake_minimum_required(VERSION 3.16)
project(dungeon)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(dungeon
    src/main.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/GameStateManager.cpp
    src/PlayState.cpp
    src/Tilemap.cpp
)

target_link_libraries(dungeon SFML::Graphics SFML::Window SFML::System)