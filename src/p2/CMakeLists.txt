cmake_minimum_required(VERSION 2.8.9)
set (CMAKE_CXX_STANDARD 11)
project (Tetris)
include_directories(include)

find_package (Threads)
find_package (Curses REQUIRED)
file(GLOB SOURCES "src/*.cpp")

add_executable(Tetris ${SOURCES})
target_link_libraries (Tetris ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Tetris ${CURSES_LIBRARIES})