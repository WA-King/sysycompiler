# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/cmake/882/bin/cmake

# The command to remove a file.
RM = /snap/cmake/882/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/workspace/mycompiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/workspace/mycompiler

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/AST.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/AST.cpp.o: src/AST.cpp
CMakeFiles/main.dir/src/AST.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/workspace/mycompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/src/AST.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/AST.cpp.o -MF CMakeFiles/main.dir/src/AST.cpp.o.d -o CMakeFiles/main.dir/src/AST.cpp.o -c /home/ubuntu/workspace/mycompiler/src/AST.cpp

CMakeFiles/main.dir/src/AST.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/AST.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/workspace/mycompiler/src/AST.cpp > CMakeFiles/main.dir/src/AST.cpp.i

CMakeFiles/main.dir/src/AST.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/AST.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/workspace/mycompiler/src/AST.cpp -o CMakeFiles/main.dir/src/AST.cpp.s

CMakeFiles/main.dir/src/RA.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/RA.cpp.o: src/RA.cpp
CMakeFiles/main.dir/src/RA.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/workspace/mycompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/RA.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/RA.cpp.o -MF CMakeFiles/main.dir/src/RA.cpp.o.d -o CMakeFiles/main.dir/src/RA.cpp.o -c /home/ubuntu/workspace/mycompiler/src/RA.cpp

CMakeFiles/main.dir/src/RA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/RA.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/workspace/mycompiler/src/RA.cpp > CMakeFiles/main.dir/src/RA.cpp.i

CMakeFiles/main.dir/src/RA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/RA.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/workspace/mycompiler/src/RA.cpp -o CMakeFiles/main.dir/src/RA.cpp.s

CMakeFiles/main.dir/src/TAC.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/TAC.cpp.o: src/TAC.cpp
CMakeFiles/main.dir/src/TAC.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/workspace/mycompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/src/TAC.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/TAC.cpp.o -MF CMakeFiles/main.dir/src/TAC.cpp.o.d -o CMakeFiles/main.dir/src/TAC.cpp.o -c /home/ubuntu/workspace/mycompiler/src/TAC.cpp

CMakeFiles/main.dir/src/TAC.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/TAC.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/workspace/mycompiler/src/TAC.cpp > CMakeFiles/main.dir/src/TAC.cpp.i

CMakeFiles/main.dir/src/TAC.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/TAC.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/workspace/mycompiler/src/TAC.cpp -o CMakeFiles/main.dir/src/TAC.cpp.s

CMakeFiles/main.dir/src/gen.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/gen.cpp.o: src/gen.cpp
CMakeFiles/main.dir/src/gen.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/workspace/mycompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/src/gen.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/gen.cpp.o -MF CMakeFiles/main.dir/src/gen.cpp.o.d -o CMakeFiles/main.dir/src/gen.cpp.o -c /home/ubuntu/workspace/mycompiler/src/gen.cpp

CMakeFiles/main.dir/src/gen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/gen.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/workspace/mycompiler/src/gen.cpp > CMakeFiles/main.dir/src/gen.cpp.i

CMakeFiles/main.dir/src/gen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/gen.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/workspace/mycompiler/src/gen.cpp -o CMakeFiles/main.dir/src/gen.cpp.s

CMakeFiles/main.dir/src/global.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/global.cpp.o: src/global.cpp
CMakeFiles/main.dir/src/global.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/workspace/mycompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/src/global.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/global.cpp.o -MF CMakeFiles/main.dir/src/global.cpp.o.d -o CMakeFiles/main.dir/src/global.cpp.o -c /home/ubuntu/workspace/mycompiler/src/global.cpp

CMakeFiles/main.dir/src/global.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/global.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/workspace/mycompiler/src/global.cpp > CMakeFiles/main.dir/src/global.cpp.i

CMakeFiles/main.dir/src/global.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/global.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/workspace/mycompiler/src/global.cpp -o CMakeFiles/main.dir/src/global.cpp.s

CMakeFiles/main.dir/src/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/main.dir/src/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/workspace/mycompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/main.cpp.o -MF CMakeFiles/main.dir/src/main.cpp.o.d -o CMakeFiles/main.dir/src/main.cpp.o -c /home/ubuntu/workspace/mycompiler/src/main.cpp

CMakeFiles/main.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/workspace/mycompiler/src/main.cpp > CMakeFiles/main.dir/src/main.cpp.i

CMakeFiles/main.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/workspace/mycompiler/src/main.cpp -o CMakeFiles/main.dir/src/main.cpp.s

CMakeFiles/main.dir/src/parser.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/parser.cpp.o: src/parser.cpp
CMakeFiles/main.dir/src/parser.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/workspace/mycompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/main.dir/src/parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/parser.cpp.o -MF CMakeFiles/main.dir/src/parser.cpp.o.d -o CMakeFiles/main.dir/src/parser.cpp.o -c /home/ubuntu/workspace/mycompiler/src/parser.cpp

CMakeFiles/main.dir/src/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/workspace/mycompiler/src/parser.cpp > CMakeFiles/main.dir/src/parser.cpp.i

CMakeFiles/main.dir/src/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/workspace/mycompiler/src/parser.cpp -o CMakeFiles/main.dir/src/parser.cpp.s

CMakeFiles/main.dir/src/scan.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/scan.cpp.o: src/scan.cpp
CMakeFiles/main.dir/src/scan.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/workspace/mycompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/main.dir/src/scan.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/scan.cpp.o -MF CMakeFiles/main.dir/src/scan.cpp.o.d -o CMakeFiles/main.dir/src/scan.cpp.o -c /home/ubuntu/workspace/mycompiler/src/scan.cpp

CMakeFiles/main.dir/src/scan.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/scan.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/workspace/mycompiler/src/scan.cpp > CMakeFiles/main.dir/src/scan.cpp.i

CMakeFiles/main.dir/src/scan.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/scan.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/workspace/mycompiler/src/scan.cpp -o CMakeFiles/main.dir/src/scan.cpp.s

CMakeFiles/main.dir/src/symbol.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/symbol.cpp.o: src/symbol.cpp
CMakeFiles/main.dir/src/symbol.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/workspace/mycompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/main.dir/src/symbol.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/symbol.cpp.o -MF CMakeFiles/main.dir/src/symbol.cpp.o.d -o CMakeFiles/main.dir/src/symbol.cpp.o -c /home/ubuntu/workspace/mycompiler/src/symbol.cpp

CMakeFiles/main.dir/src/symbol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/symbol.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/workspace/mycompiler/src/symbol.cpp > CMakeFiles/main.dir/src/symbol.cpp.i

CMakeFiles/main.dir/src/symbol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/symbol.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/workspace/mycompiler/src/symbol.cpp -o CMakeFiles/main.dir/src/symbol.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/AST.cpp.o" \
"CMakeFiles/main.dir/src/RA.cpp.o" \
"CMakeFiles/main.dir/src/TAC.cpp.o" \
"CMakeFiles/main.dir/src/gen.cpp.o" \
"CMakeFiles/main.dir/src/global.cpp.o" \
"CMakeFiles/main.dir/src/main.cpp.o" \
"CMakeFiles/main.dir/src/parser.cpp.o" \
"CMakeFiles/main.dir/src/scan.cpp.o" \
"CMakeFiles/main.dir/src/symbol.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/src/AST.cpp.o
main: CMakeFiles/main.dir/src/RA.cpp.o
main: CMakeFiles/main.dir/src/TAC.cpp.o
main: CMakeFiles/main.dir/src/gen.cpp.o
main: CMakeFiles/main.dir/src/global.cpp.o
main: CMakeFiles/main.dir/src/main.cpp.o
main: CMakeFiles/main.dir/src/parser.cpp.o
main: CMakeFiles/main.dir/src/scan.cpp.o
main: CMakeFiles/main.dir/src/symbol.cpp.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/workspace/mycompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/ubuntu/workspace/mycompiler && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/workspace/mycompiler /home/ubuntu/workspace/mycompiler /home/ubuntu/workspace/mycompiler /home/ubuntu/workspace/mycompiler /home/ubuntu/workspace/mycompiler/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

