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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.13.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.13.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alexandrebouvier/Documents/srv_fire

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alexandrebouvier/Documents/srv_fire

# Include any dependencies generated for this target.
include CMakeFiles/srv_fire.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/srv_fire.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/srv_fire.dir/flags.make

CMakeFiles/srv_fire.dir/main.cpp.o: CMakeFiles/srv_fire.dir/flags.make
CMakeFiles/srv_fire.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/srv_fire.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/srv_fire.dir/main.cpp.o -c /Users/alexandrebouvier/Documents/srv_fire/main.cpp

CMakeFiles/srv_fire.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srv_fire.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandrebouvier/Documents/srv_fire/main.cpp > CMakeFiles/srv_fire.dir/main.cpp.i

CMakeFiles/srv_fire.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srv_fire.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandrebouvier/Documents/srv_fire/main.cpp -o CMakeFiles/srv_fire.dir/main.cpp.s

CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.o: CMakeFiles/srv_fire.dir/flags.make
CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.o: network/src/BusinessLogicManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.o -c /Users/alexandrebouvier/Documents/srv_fire/network/src/BusinessLogicManager.cpp

CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandrebouvier/Documents/srv_fire/network/src/BusinessLogicManager.cpp > CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.i

CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandrebouvier/Documents/srv_fire/network/src/BusinessLogicManager.cpp -o CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.s

CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.o: CMakeFiles/srv_fire.dir/flags.make
CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.o: network/src/connectionHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.o -c /Users/alexandrebouvier/Documents/srv_fire/network/src/connectionHandler.cpp

CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandrebouvier/Documents/srv_fire/network/src/connectionHandler.cpp > CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.i

CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandrebouvier/Documents/srv_fire/network/src/connectionHandler.cpp -o CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.s

CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.o: CMakeFiles/srv_fire.dir/flags.make
CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.o: network/src/PacketHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.o -c /Users/alexandrebouvier/Documents/srv_fire/network/src/PacketHandler.cpp

CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandrebouvier/Documents/srv_fire/network/src/PacketHandler.cpp > CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.i

CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandrebouvier/Documents/srv_fire/network/src/PacketHandler.cpp -o CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.s

CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.o: CMakeFiles/srv_fire.dir/flags.make
CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.o: network/src/CommandAnalyzer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.o -c /Users/alexandrebouvier/Documents/srv_fire/network/src/CommandAnalyzer.cpp

CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandrebouvier/Documents/srv_fire/network/src/CommandAnalyzer.cpp > CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.i

CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandrebouvier/Documents/srv_fire/network/src/CommandAnalyzer.cpp -o CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.s

CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.o: CMakeFiles/srv_fire.dir/flags.make
CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.o: network/src/ProtocolManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.o -c /Users/alexandrebouvier/Documents/srv_fire/network/src/ProtocolManager.cpp

CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandrebouvier/Documents/srv_fire/network/src/ProtocolManager.cpp > CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.i

CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandrebouvier/Documents/srv_fire/network/src/ProtocolManager.cpp -o CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.s

CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.o: CMakeFiles/srv_fire.dir/flags.make
CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.o: Utilitary/sources/ClientNetwork.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.o -c /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/ClientNetwork.cpp

CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/ClientNetwork.cpp > CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.i

CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/ClientNetwork.cpp -o CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.s

CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.o: CMakeFiles/srv_fire.dir/flags.make
CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.o: Utilitary/sources/Error.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.o -c /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/Error.cpp

CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/Error.cpp > CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.i

CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/Error.cpp -o CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.s

CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.o: CMakeFiles/srv_fire.dir/flags.make
CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.o: Utilitary/sources/LogNetwork.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.o -c /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/LogNetwork.cpp

CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/LogNetwork.cpp > CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.i

CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/LogNetwork.cpp -o CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.s

CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.o: CMakeFiles/srv_fire.dir/flags.make
CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.o: Utilitary/sources/Log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.o -c /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/Log.cpp

CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/Log.cpp > CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.i

CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexandrebouvier/Documents/srv_fire/Utilitary/sources/Log.cpp -o CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.s

# Object files for target srv_fire
srv_fire_OBJECTS = \
"CMakeFiles/srv_fire.dir/main.cpp.o" \
"CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.o" \
"CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.o" \
"CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.o" \
"CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.o" \
"CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.o" \
"CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.o" \
"CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.o" \
"CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.o" \
"CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.o"

# External object files for target srv_fire
srv_fire_EXTERNAL_OBJECTS =

srv_fire: CMakeFiles/srv_fire.dir/main.cpp.o
srv_fire: CMakeFiles/srv_fire.dir/network/src/BusinessLogicManager.cpp.o
srv_fire: CMakeFiles/srv_fire.dir/network/src/connectionHandler.cpp.o
srv_fire: CMakeFiles/srv_fire.dir/network/src/PacketHandler.cpp.o
srv_fire: CMakeFiles/srv_fire.dir/network/src/CommandAnalyzer.cpp.o
srv_fire: CMakeFiles/srv_fire.dir/network/src/ProtocolManager.cpp.o
srv_fire: CMakeFiles/srv_fire.dir/Utilitary/sources/ClientNetwork.cpp.o
srv_fire: CMakeFiles/srv_fire.dir/Utilitary/sources/Error.cpp.o
srv_fire: CMakeFiles/srv_fire.dir/Utilitary/sources/LogNetwork.cpp.o
srv_fire: CMakeFiles/srv_fire.dir/Utilitary/sources/Log.cpp.o
srv_fire: CMakeFiles/srv_fire.dir/build.make
srv_fire: CMakeFiles/srv_fire.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alexandrebouvier/Documents/srv_fire/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable srv_fire"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/srv_fire.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/srv_fire.dir/build: srv_fire

.PHONY : CMakeFiles/srv_fire.dir/build

CMakeFiles/srv_fire.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/srv_fire.dir/cmake_clean.cmake
.PHONY : CMakeFiles/srv_fire.dir/clean

CMakeFiles/srv_fire.dir/depend:
	cd /Users/alexandrebouvier/Documents/srv_fire && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alexandrebouvier/Documents/srv_fire /Users/alexandrebouvier/Documents/srv_fire /Users/alexandrebouvier/Documents/srv_fire /Users/alexandrebouvier/Documents/srv_fire /Users/alexandrebouvier/Documents/srv_fire/CMakeFiles/srv_fire.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/srv_fire.dir/depend

