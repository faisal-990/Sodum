# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/faisal/Sodum

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/faisal/Sodum/build

# Include any dependencies generated for this target.
include CMakeFiles/SodumRunner.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SodumRunner.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SodumRunner.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SodumRunner.dir/flags.make

CMakeFiles/SodumRunner.dir/src/main.cpp.o: CMakeFiles/SodumRunner.dir/flags.make
CMakeFiles/SodumRunner.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/SodumRunner.dir/src/main.cpp.o: CMakeFiles/SodumRunner.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/faisal/Sodum/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SodumRunner.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SodumRunner.dir/src/main.cpp.o -MF CMakeFiles/SodumRunner.dir/src/main.cpp.o.d -o CMakeFiles/SodumRunner.dir/src/main.cpp.o -c /home/faisal/Sodum/src/main.cpp

CMakeFiles/SodumRunner.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SodumRunner.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/faisal/Sodum/src/main.cpp > CMakeFiles/SodumRunner.dir/src/main.cpp.i

CMakeFiles/SodumRunner.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SodumRunner.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/faisal/Sodum/src/main.cpp -o CMakeFiles/SodumRunner.dir/src/main.cpp.s

# Object files for target SodumRunner
SodumRunner_OBJECTS = \
"CMakeFiles/SodumRunner.dir/src/main.cpp.o"

# External object files for target SodumRunner
SodumRunner_EXTERNAL_OBJECTS =

SodumRunner: CMakeFiles/SodumRunner.dir/src/main.cpp.o
SodumRunner: CMakeFiles/SodumRunner.dir/build.make
SodumRunner: CMakeFiles/SodumRunner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/faisal/Sodum/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SodumRunner"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Running clang-format before building SodumRunner"
	../clang-format.sh
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SodumRunner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SodumRunner.dir/build: SodumRunner
.PHONY : CMakeFiles/SodumRunner.dir/build

CMakeFiles/SodumRunner.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SodumRunner.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SodumRunner.dir/clean

CMakeFiles/SodumRunner.dir/depend:
	cd /home/faisal/Sodum/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/faisal/Sodum /home/faisal/Sodum /home/faisal/Sodum/build /home/faisal/Sodum/build /home/faisal/Sodum/build/CMakeFiles/SodumRunner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SodumRunner.dir/depend

