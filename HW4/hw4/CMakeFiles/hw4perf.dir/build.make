# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/student/Desktop/vm-share/CPSC223/Week4/hw4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/student/Desktop/vm-share/CPSC223/Week4/hw4

# Include any dependencies generated for this target.
include CMakeFiles/hw4perf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw4perf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw4perf.dir/flags.make

CMakeFiles/hw4perf.dir/hw4_perf.cpp.o: CMakeFiles/hw4perf.dir/flags.make
CMakeFiles/hw4perf.dir/hw4_perf.cpp.o: hw4_perf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/vm-share/CPSC223/Week4/hw4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw4perf.dir/hw4_perf.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw4perf.dir/hw4_perf.cpp.o -c /home/student/Desktop/vm-share/CPSC223/Week4/hw4/hw4_perf.cpp

CMakeFiles/hw4perf.dir/hw4_perf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw4perf.dir/hw4_perf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/student/Desktop/vm-share/CPSC223/Week4/hw4/hw4_perf.cpp > CMakeFiles/hw4perf.dir/hw4_perf.cpp.i

CMakeFiles/hw4perf.dir/hw4_perf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw4perf.dir/hw4_perf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/student/Desktop/vm-share/CPSC223/Week4/hw4/hw4_perf.cpp -o CMakeFiles/hw4perf.dir/hw4_perf.cpp.s

# Object files for target hw4perf
hw4perf_OBJECTS = \
"CMakeFiles/hw4perf.dir/hw4_perf.cpp.o"

# External object files for target hw4perf
hw4perf_EXTERNAL_OBJECTS =

hw4perf: CMakeFiles/hw4perf.dir/hw4_perf.cpp.o
hw4perf: CMakeFiles/hw4perf.dir/build.make
hw4perf: CMakeFiles/hw4perf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/student/Desktop/vm-share/CPSC223/Week4/hw4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw4perf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw4perf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw4perf.dir/build: hw4perf

.PHONY : CMakeFiles/hw4perf.dir/build

CMakeFiles/hw4perf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw4perf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw4perf.dir/clean

CMakeFiles/hw4perf.dir/depend:
	cd /home/student/Desktop/vm-share/CPSC223/Week4/hw4 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/student/Desktop/vm-share/CPSC223/Week4/hw4 /home/student/Desktop/vm-share/CPSC223/Week4/hw4 /home/student/Desktop/vm-share/CPSC223/Week4/hw4 /home/student/Desktop/vm-share/CPSC223/Week4/hw4 /home/student/Desktop/vm-share/CPSC223/Week4/hw4/CMakeFiles/hw4perf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw4perf.dir/depend

