cmake_minimum_required(VERSION 3.10)
project(Sodum)

set(CMAKE_CXX_STANDARD 17)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Include directories
include_directories(include)

# Create executable
add_executable(sodum ${SOURCES})

# Format code before building
add_custom_target(
    format
    COMMAND clang-format -i ${SOURCES} ${HEADERS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
add_dependencies(sodum format)
