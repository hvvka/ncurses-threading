cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 14)
project (Archers)
include_directories(include)

find_package (Threads)
find_package (Curses REQUIRED)
file(GLOB SOURCES "src/*.cpp")

add_executable(Archers ${SOURCES})
target_link_libraries(Archers ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES})