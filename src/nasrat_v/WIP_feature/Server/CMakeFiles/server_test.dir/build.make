# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_SOURCE_DIR = /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server

# Include any dependencies generated for this target.
include CMakeFiles/server_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server_test.dir/flags.make

CMakeFiles/server_test.dir/source/ServerNetwork.cpp.o: CMakeFiles/server_test.dir/flags.make
CMakeFiles/server_test.dir/source/ServerNetwork.cpp.o: source/ServerNetwork.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server_test.dir/source/ServerNetwork.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_test.dir/source/ServerNetwork.cpp.o -c /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/ServerNetwork.cpp

CMakeFiles/server_test.dir/source/ServerNetwork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_test.dir/source/ServerNetwork.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/ServerNetwork.cpp > CMakeFiles/server_test.dir/source/ServerNetwork.cpp.i

CMakeFiles/server_test.dir/source/ServerNetwork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_test.dir/source/ServerNetwork.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/ServerNetwork.cpp -o CMakeFiles/server_test.dir/source/ServerNetwork.cpp.s

CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.o: CMakeFiles/server_test.dir/flags.make
CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.o: source/ProcessCommunication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.o -c /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/ProcessCommunication.cpp

CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/ProcessCommunication.cpp > CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.i

CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/ProcessCommunication.cpp -o CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.s

CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.o: CMakeFiles/server_test.dir/flags.make
CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.o: source/Log/LogNetwork.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.o -c /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/Log/LogNetwork.cpp

CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/Log/LogNetwork.cpp > CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.i

CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/Log/LogNetwork.cpp -o CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.s

CMakeFiles/server_test.dir/source/Main.cpp.o: CMakeFiles/server_test.dir/flags.make
CMakeFiles/server_test.dir/source/Main.cpp.o: source/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server_test.dir/source/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_test.dir/source/Main.cpp.o -c /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/Main.cpp

CMakeFiles/server_test.dir/source/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_test.dir/source/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/Main.cpp > CMakeFiles/server_test.dir/source/Main.cpp.i

CMakeFiles/server_test.dir/source/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_test.dir/source/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/source/Main.cpp -o CMakeFiles/server_test.dir/source/Main.cpp.s

# Object files for target server_test
server_test_OBJECTS = \
"CMakeFiles/server_test.dir/source/ServerNetwork.cpp.o" \
"CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.o" \
"CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.o" \
"CMakeFiles/server_test.dir/source/Main.cpp.o"

# External object files for target server_test
server_test_EXTERNAL_OBJECTS =

server_test: CMakeFiles/server_test.dir/source/ServerNetwork.cpp.o
server_test: CMakeFiles/server_test.dir/source/ProcessCommunication.cpp.o
server_test: CMakeFiles/server_test.dir/source/Log/LogNetwork.cpp.o
server_test: CMakeFiles/server_test.dir/source/Main.cpp.o
server_test: CMakeFiles/server_test.dir/build.make
server_test: CMakeFiles/server_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable server_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server_test.dir/build: server_test

.PHONY : CMakeFiles/server_test.dir/build

CMakeFiles/server_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server_test.dir/clean

CMakeFiles/server_test.dir/depend:
	cd /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server /home/nasrat_v/Dev/srv_fire/src/nasrat_v/WIP_feature/Server/CMakeFiles/server_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server_test.dir/depend

