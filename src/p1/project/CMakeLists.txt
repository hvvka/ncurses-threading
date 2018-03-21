cmake_minimum_required(VERSION 2.8.9)
set (CMAKE_CXX_STANDARD 11)
project (Snake)
#[[include_directories(include)]]

find_package (Threads)
find_package (Curses REQUIRED)
file(GLOB SOURCES "src/*.cpp")

add_executable(Snake ${SOURCES})
target_link_libraries (Snake ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (Snake ${CURSES_LIBRARIES})
