#!/bin/bash

# Define the source directory if CMAKE_SOURCE_DIR is not available
SRC_DIR="../Sodum"

# Run clang-format with the correct syntax and allow wildcard expansion
clang-format -i --style="LLVM" ${SRC_DIR}/src/*.cpp

