# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build

# Include any dependencies generated for this target.
include src/ch12/CMakeFiles/ch12.dir/depend.make

# Include the progress variables for this target.
include src/ch12/CMakeFiles/ch12.dir/progress.make

# Include the compile flags for this target's objects.
include src/ch12/CMakeFiles/ch12.dir/flags.make

src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o: src/ch12/CMakeFiles/ch12.dir/flags.make
src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o: ../src/ch12/chpater12.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o"
	cd /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch12 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ch12.dir/chpater12.cc.o -c /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/src/ch12/chpater12.cc

src/ch12/CMakeFiles/ch12.dir/chpater12.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ch12.dir/chpater12.cc.i"
	cd /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch12 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/src/ch12/chpater12.cc > CMakeFiles/ch12.dir/chpater12.cc.i

src/ch12/CMakeFiles/ch12.dir/chpater12.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ch12.dir/chpater12.cc.s"
	cd /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch12 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/src/ch12/chpater12.cc -o CMakeFiles/ch12.dir/chpater12.cc.s

src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o.requires:

.PHONY : src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o.requires

src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o.provides: src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o.requires
	$(MAKE) -f src/ch12/CMakeFiles/ch12.dir/build.make src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o.provides.build
.PHONY : src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o.provides

src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o.provides.build: src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o


# Object files for target ch12
ch12_OBJECTS = \
"CMakeFiles/ch12.dir/chpater12.cc.o"

# External object files for target ch12
ch12_EXTERNAL_OBJECTS =

ch12: src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o
ch12: src/ch12/CMakeFiles/ch12.dir/build.make
ch12: src/ch12/CMakeFiles/ch12.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../ch12"
	cd /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch12 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ch12.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/ch12/CMakeFiles/ch12.dir/build: ch12

.PHONY : src/ch12/CMakeFiles/ch12.dir/build

src/ch12/CMakeFiles/ch12.dir/requires: src/ch12/CMakeFiles/ch12.dir/chpater12.cc.o.requires

.PHONY : src/ch12/CMakeFiles/ch12.dir/requires

src/ch12/CMakeFiles/ch12.dir/clean:
	cd /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch12 && $(CMAKE_COMMAND) -P CMakeFiles/ch12.dir/cmake_clean.cmake
.PHONY : src/ch12/CMakeFiles/ch12.dir/clean

src/ch12/CMakeFiles/ch12.dir/depend:
	cd /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/src/ch12 /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch12 /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch12/CMakeFiles/ch12.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/ch12/CMakeFiles/ch12.dir/depend

