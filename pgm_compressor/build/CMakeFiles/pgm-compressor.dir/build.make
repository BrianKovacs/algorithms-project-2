# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor/build

# Include any dependencies generated for this target.
include CMakeFiles/pgm-compressor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pgm-compressor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pgm-compressor.dir/flags.make

CMakeFiles/pgm-compressor.dir/main.cpp.o: CMakeFiles/pgm-compressor.dir/flags.make
CMakeFiles/pgm-compressor.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pgm-compressor.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pgm-compressor.dir/main.cpp.o -c /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor/main.cpp

CMakeFiles/pgm-compressor.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pgm-compressor.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor/main.cpp > CMakeFiles/pgm-compressor.dir/main.cpp.i

CMakeFiles/pgm-compressor.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pgm-compressor.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor/main.cpp -o CMakeFiles/pgm-compressor.dir/main.cpp.s

CMakeFiles/pgm-compressor.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/pgm-compressor.dir/main.cpp.o.requires

CMakeFiles/pgm-compressor.dir/main.cpp.o.provides: CMakeFiles/pgm-compressor.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/pgm-compressor.dir/build.make CMakeFiles/pgm-compressor.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/pgm-compressor.dir/main.cpp.o.provides

CMakeFiles/pgm-compressor.dir/main.cpp.o.provides.build: CMakeFiles/pgm-compressor.dir/main.cpp.o


# Object files for target pgm-compressor
pgm__compressor_OBJECTS = \
"CMakeFiles/pgm-compressor.dir/main.cpp.o"

# External object files for target pgm-compressor
pgm__compressor_EXTERNAL_OBJECTS =

pgm-compressor: CMakeFiles/pgm-compressor.dir/main.cpp.o
pgm-compressor: CMakeFiles/pgm-compressor.dir/build.make
pgm-compressor: CMakeFiles/pgm-compressor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pgm-compressor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pgm-compressor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pgm-compressor.dir/build: pgm-compressor

.PHONY : CMakeFiles/pgm-compressor.dir/build

CMakeFiles/pgm-compressor.dir/requires: CMakeFiles/pgm-compressor.dir/main.cpp.o.requires

.PHONY : CMakeFiles/pgm-compressor.dir/requires

CMakeFiles/pgm-compressor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pgm-compressor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pgm-compressor.dir/clean

CMakeFiles/pgm-compressor.dir/depend:
	cd /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor/build /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor/build /Users/Brian/Documents/GitHub/algorithms-project-2/pgm_compressor/build/CMakeFiles/pgm-compressor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pgm-compressor.dir/depend
