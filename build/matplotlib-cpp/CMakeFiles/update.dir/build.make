# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /home/clan-nur/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/clan-nur/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/clan-nur/Graph_Tuner_Test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/clan-nur/Graph_Tuner_Test/build

# Include any dependencies generated for this target.
include matplotlib-cpp/CMakeFiles/update.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include matplotlib-cpp/CMakeFiles/update.dir/compiler_depend.make

# Include the progress variables for this target.
include matplotlib-cpp/CMakeFiles/update.dir/progress.make

# Include the compile flags for this target's objects.
include matplotlib-cpp/CMakeFiles/update.dir/flags.make

matplotlib-cpp/CMakeFiles/update.dir/examples/update.cpp.o: matplotlib-cpp/CMakeFiles/update.dir/flags.make
matplotlib-cpp/CMakeFiles/update.dir/examples/update.cpp.o: /home/clan-nur/Graph_Tuner_Test/matplotlib-cpp/examples/update.cpp
matplotlib-cpp/CMakeFiles/update.dir/examples/update.cpp.o: matplotlib-cpp/CMakeFiles/update.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/clan-nur/Graph_Tuner_Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object matplotlib-cpp/CMakeFiles/update.dir/examples/update.cpp.o"
	cd /home/clan-nur/Graph_Tuner_Test/build/matplotlib-cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT matplotlib-cpp/CMakeFiles/update.dir/examples/update.cpp.o -MF CMakeFiles/update.dir/examples/update.cpp.o.d -o CMakeFiles/update.dir/examples/update.cpp.o -c /home/clan-nur/Graph_Tuner_Test/matplotlib-cpp/examples/update.cpp

matplotlib-cpp/CMakeFiles/update.dir/examples/update.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/update.dir/examples/update.cpp.i"
	cd /home/clan-nur/Graph_Tuner_Test/build/matplotlib-cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/clan-nur/Graph_Tuner_Test/matplotlib-cpp/examples/update.cpp > CMakeFiles/update.dir/examples/update.cpp.i

matplotlib-cpp/CMakeFiles/update.dir/examples/update.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/update.dir/examples/update.cpp.s"
	cd /home/clan-nur/Graph_Tuner_Test/build/matplotlib-cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/clan-nur/Graph_Tuner_Test/matplotlib-cpp/examples/update.cpp -o CMakeFiles/update.dir/examples/update.cpp.s

# Object files for target update
update_OBJECTS = \
"CMakeFiles/update.dir/examples/update.cpp.o"

# External object files for target update
update_EXTERNAL_OBJECTS =

bin/update: matplotlib-cpp/CMakeFiles/update.dir/examples/update.cpp.o
bin/update: matplotlib-cpp/CMakeFiles/update.dir/build.make
bin/update: /usr/lib/x86_64-linux-gnu/libpython3.8.so
bin/update: matplotlib-cpp/CMakeFiles/update.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/clan-nur/Graph_Tuner_Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/update"
	cd /home/clan-nur/Graph_Tuner_Test/build/matplotlib-cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/update.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
matplotlib-cpp/CMakeFiles/update.dir/build: bin/update
.PHONY : matplotlib-cpp/CMakeFiles/update.dir/build

matplotlib-cpp/CMakeFiles/update.dir/clean:
	cd /home/clan-nur/Graph_Tuner_Test/build/matplotlib-cpp && $(CMAKE_COMMAND) -P CMakeFiles/update.dir/cmake_clean.cmake
.PHONY : matplotlib-cpp/CMakeFiles/update.dir/clean

matplotlib-cpp/CMakeFiles/update.dir/depend:
	cd /home/clan-nur/Graph_Tuner_Test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/clan-nur/Graph_Tuner_Test /home/clan-nur/Graph_Tuner_Test/matplotlib-cpp /home/clan-nur/Graph_Tuner_Test/build /home/clan-nur/Graph_Tuner_Test/build/matplotlib-cpp /home/clan-nur/Graph_Tuner_Test/build/matplotlib-cpp/CMakeFiles/update.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : matplotlib-cpp/CMakeFiles/update.dir/depend

