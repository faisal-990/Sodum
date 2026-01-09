cmake_minimum_required(VERSION 3.10)
project(Sodum)

# 1. Standard and LLVM Discovery
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(LLVM REQUIRED CONFIG)

# 2. Compiler Flags and Includes
# We keep your debug flags but add LLVM's required definitions
set(CMAKE_BUILD_TYPE Debug)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR}/include ${LLVM_INCLUDE_DIRS})

# 3. LLVM Component Mapping
# 'core' for IR, 'native' for your CPU, 'support' for tools
llvm_map_components_to_libnames(llvm_libs core support native target)
set(EXTERNAL_LIBS "z" "tinfo" "pthread" "dl")

# 4. Source and Header Discovery
file(GLOB SOURCES 
    "src/main.cpp"
    "src/lexer.cpp"
    "src/parser_v1.0.cpp"
    "src/visitors/ast_accept.cpp"
    "src/visitors/ast_printer.cpp"
    "src/visitors/llvm_codegen.cpp"
)

file(GLOB HEADERS 
    "include/tokens.hpp"
    "include/lexer/lexer.hpp"
    "include/parser/parser_v1.hpp"
    "include/parser/ast_v1.1.hpp"
    "include/visitor/ast_visitor.hpp"
    "include/visitor/visitor.hpp"
    "include/visitor/llvm_codegen.hpp"
)

# 5. Create Executable
add_executable(sodum ${SOURCES} ${HEADERS})

# 6. Linkage - Crucial for LLVM
target_link_libraries(sodum ${llvm_libs} ${EXTERNAL_LIBS})

# 7. Formatting tool
add_custom_target(
    format
    COMMAND clang-format --style=LLVM -i ${SOURCES} ${HEADERS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
