cmake_minimum_required(VERSION 3.10)

project(Sodum)

# Specify the source files for the project
set(SOURCES
    src/main.cpp
)

# Create an executable target named 'my_executable'
add_executable(SodumRunner ${SOURCES})

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add a custom command that runs clang-format on all source files before building the executable
add_custom_command(
    TARGET SodumRunner
    PRE_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/clang-format.sh
    COMMENT "Running clang-format before building SodumRunner"
)
