# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/squin/programming/judo_engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/squin/programming/judo_engine/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/judo_engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/judo_engine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/judo_engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/judo_engine.dir/flags.make

CMakeFiles/judo_engine.dir/JudoEngine.cpp.o: CMakeFiles/judo_engine.dir/flags.make
CMakeFiles/judo_engine.dir/JudoEngine.cpp.o: /home/squin/programming/judo_engine/JudoEngine.cpp
CMakeFiles/judo_engine.dir/JudoEngine.cpp.o: CMakeFiles/judo_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/squin/programming/judo_engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/judo_engine.dir/JudoEngine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/judo_engine.dir/JudoEngine.cpp.o -MF CMakeFiles/judo_engine.dir/JudoEngine.cpp.o.d -o CMakeFiles/judo_engine.dir/JudoEngine.cpp.o -c /home/squin/programming/judo_engine/JudoEngine.cpp

CMakeFiles/judo_engine.dir/JudoEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/judo_engine.dir/JudoEngine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/squin/programming/judo_engine/JudoEngine.cpp > CMakeFiles/judo_engine.dir/JudoEngine.cpp.i

CMakeFiles/judo_engine.dir/JudoEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/judo_engine.dir/JudoEngine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/squin/programming/judo_engine/JudoEngine.cpp -o CMakeFiles/judo_engine.dir/JudoEngine.cpp.s

CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.o: CMakeFiles/judo_engine.dir/flags.make
CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.o: /home/squin/programming/judo_engine/DualDynamicArray.cpp
CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.o: CMakeFiles/judo_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/squin/programming/judo_engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.o -MF CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.o.d -o CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.o -c /home/squin/programming/judo_engine/DualDynamicArray.cpp

CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/squin/programming/judo_engine/DualDynamicArray.cpp > CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.i

CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/squin/programming/judo_engine/DualDynamicArray.cpp -o CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.s

CMakeFiles/judo_engine.dir/judo.cpp.o: CMakeFiles/judo_engine.dir/flags.make
CMakeFiles/judo_engine.dir/judo.cpp.o: /home/squin/programming/judo_engine/judo.cpp
CMakeFiles/judo_engine.dir/judo.cpp.o: CMakeFiles/judo_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/squin/programming/judo_engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/judo_engine.dir/judo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/judo_engine.dir/judo.cpp.o -MF CMakeFiles/judo_engine.dir/judo.cpp.o.d -o CMakeFiles/judo_engine.dir/judo.cpp.o -c /home/squin/programming/judo_engine/judo.cpp

CMakeFiles/judo_engine.dir/judo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/judo_engine.dir/judo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/squin/programming/judo_engine/judo.cpp > CMakeFiles/judo_engine.dir/judo.cpp.i

CMakeFiles/judo_engine.dir/judo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/judo_engine.dir/judo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/squin/programming/judo_engine/judo.cpp -o CMakeFiles/judo_engine.dir/judo.cpp.s

# Object files for target judo_engine
judo_engine_OBJECTS = \
"CMakeFiles/judo_engine.dir/JudoEngine.cpp.o" \
"CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.o" \
"CMakeFiles/judo_engine.dir/judo.cpp.o"

# External object files for target judo_engine
judo_engine_EXTERNAL_OBJECTS =

judo_engine: CMakeFiles/judo_engine.dir/JudoEngine.cpp.o
judo_engine: CMakeFiles/judo_engine.dir/DualDynamicArray.cpp.o
judo_engine: CMakeFiles/judo_engine.dir/judo.cpp.o
judo_engine: CMakeFiles/judo_engine.dir/build.make
judo_engine: CMakeFiles/judo_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/squin/programming/judo_engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable judo_engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/judo_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/judo_engine.dir/build: judo_engine
.PHONY : CMakeFiles/judo_engine.dir/build

CMakeFiles/judo_engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/judo_engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/judo_engine.dir/clean

CMakeFiles/judo_engine.dir/depend:
	cd /home/squin/programming/judo_engine/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/squin/programming/judo_engine /home/squin/programming/judo_engine /home/squin/programming/judo_engine/cmake-build-debug /home/squin/programming/judo_engine/cmake-build-debug /home/squin/programming/judo_engine/cmake-build-debug/CMakeFiles/judo_engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/judo_engine.dir/depend

