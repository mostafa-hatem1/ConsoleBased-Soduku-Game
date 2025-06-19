cmake_minimum_required(VERSION 3.16)
project(SudokuProject)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create options for optional features
option(BUILD_GENERATOR "Build the SudokuGenerator module for puzzle generation" ON)


# Include headers from src directory
include_directories(${CMAKE_SOURCE_DIR}/src)

# Core source files
set(SOURCES
    src/main.cpp
    src/SudokuBoard.cpp
    src/SudokuSolver.cpp
    src/SudokuGame.cpp
)

# Header files (not required by CMake, but useful for clarity)
set(HEADERS
    src/SudokuBoard.hpp
    src/SudokuSolver.hpp
    src/SudokuGame.hpp
)

# If building puzzle generator, include its source/header
if(BUILD_GENERATOR)
    list(APPEND SOURCES src/SudokuGenerator.cpp)
    list(APPEND HEADERS src/SudokuGenerator.hpp)
endif()

# If building advanced checks, include those source/header


# Create the final executable
add_executable(SudokuProject ${SOURCES} ${HEADERS})
