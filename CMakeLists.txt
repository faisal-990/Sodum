cmake_minimum_required(VERSION 3.10)
project(Sodum)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-g -O0")
# Add source files - removed the extra space after "src/main.cpp"
file(GLOB SOURCES 
    "src/main.cpp"
    "src/lexer.cpp"
    "src/parser_v1.0.cpp"
    "src/visitors/ast_accept.cpp"
    "src/visitors/ast_printer.cpp"
)

# Add header files
file(GLOB HEADERS 
    "include/tokens.hpp"
    "include/lexer/lexer.hpp"
    "include/parser/parser_v1.hpp"
    "include/parser/ast_v1.1.hpp"
    "include/visitor/ast_visitor.hpp"
    "include/visitor/visitor.hpp"
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)


# Create executable
add_executable(sodum ${SOURCES} ${HEADERS})

# Format code before building
add_custom_target(
    format
    COMMAND clang-format --style=LLVM -i ${SOURCES} ${HEADERS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Ensure that the format target runs before the executable is built
#add_dependencies(sodum format)
