cmake_minimum_required(VERSION 3.10)
project(Sodum)

set(CMAKE_CXX_STANDARD 17)

# Add source files
file(GLOB SOURCES "src/*.cpp")  # Glob all .cpp files in src directory

# Add header files
file(GLOB HEADERS "include/*.hpp")  # Glob all .hpp files in include directory

# Include directories
include_directories(include)

# Create executable
add_executable(sodum ${SOURCES} ${HEADERS})  # Include headers in the target

# Format code before building
add_custom_target(
    format
    COMMAND clang-format -i ${SOURCES} ${HEADERS}  # Space between ${SOURCES} and ${HEADERS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Ensure that the format target runs before the executable is built
add_dependencies(sodum format)

