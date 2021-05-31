cmake_minimum_required(VERSION 3.17)
project(BatNav)

set(CMAKE_CXX_STANDARD 14)

add_executable(BatNavProject main.cpp Engine/Game.cpp Engine/Game.h)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(BatNavProject sfml-system sfml-window sfml-graphics sfml-audio sfml-network)