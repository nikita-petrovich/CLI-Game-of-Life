cmake_minimum_required(VERSION 3.10.0)
project(CLI-Game-of-Life VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wunused -Wsign-conversion -Wpedantic)

add_executable(CLI-Game-of-Life src/main.cpp src/Game.cpp)

