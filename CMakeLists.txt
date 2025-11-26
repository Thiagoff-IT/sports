cmake_minimum_required(VERSION 3.16)
project(sport)

set(CMAKE_CXX_STANDARD 20)

# Include all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(sport main.cpp ${SOURCES})
