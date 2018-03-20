cmake_minimum_required(VERSION 2.8.9)
set (CMAKE_CXX_STANDARD 11)
project (Snake)

find_package (Snake)
find_package (Curses REQUIRED)

add_executable(Snake Snake.cpp)
target_link_libraries (Snake ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Snake ${CURSES_LIBRARIES})