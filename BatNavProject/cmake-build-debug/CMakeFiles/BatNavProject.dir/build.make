# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/BatNavProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BatNavProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BatNavProject.dir/flags.make

CMakeFiles/BatNavProject.dir/main.cpp.o: CMakeFiles/BatNavProject.dir/flags.make
CMakeFiles/BatNavProject.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BatNavProject.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BatNavProject.dir/main.cpp.o -c /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/main.cpp

CMakeFiles/BatNavProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BatNavProject.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/main.cpp > CMakeFiles/BatNavProject.dir/main.cpp.i

CMakeFiles/BatNavProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BatNavProject.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/main.cpp -o CMakeFiles/BatNavProject.dir/main.cpp.s

CMakeFiles/BatNavProject.dir/Engine/Game.cpp.o: CMakeFiles/BatNavProject.dir/flags.make
CMakeFiles/BatNavProject.dir/Engine/Game.cpp.o: ../Engine/Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BatNavProject.dir/Engine/Game.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BatNavProject.dir/Engine/Game.cpp.o -c /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Game.cpp

CMakeFiles/BatNavProject.dir/Engine/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BatNavProject.dir/Engine/Game.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Game.cpp > CMakeFiles/BatNavProject.dir/Engine/Game.cpp.i

CMakeFiles/BatNavProject.dir/Engine/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BatNavProject.dir/Engine/Game.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Game.cpp -o CMakeFiles/BatNavProject.dir/Engine/Game.cpp.s

CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.o: CMakeFiles/BatNavProject.dir/flags.make
CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.o: ../Gameplay/GameManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.o -c /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Gameplay/GameManager.cpp

CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Gameplay/GameManager.cpp > CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.i

CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Gameplay/GameManager.cpp -o CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.s

CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.o: CMakeFiles/BatNavProject.dir/flags.make
CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.o: ../Gameplay/Board/Board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.o -c /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Gameplay/Board/Board.cpp

CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Gameplay/Board/Board.cpp > CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.i

CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Gameplay/Board/Board.cpp -o CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.s

CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.o: CMakeFiles/BatNavProject.dir/flags.make
CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.o: ../Engine/Input/InputManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.o -c /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Input/InputManager.cpp

CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Input/InputManager.cpp > CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.i

CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Input/InputManager.cpp -o CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.s

CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.o: CMakeFiles/BatNavProject.dir/flags.make
CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.o: ../Engine/Event/EventManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.o -c /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/EventManager.cpp

CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/EventManager.cpp > CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.i

CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/EventManager.cpp -o CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.s

CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.o: CMakeFiles/BatNavProject.dir/flags.make
CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.o: ../Engine/Event/Listener/IEventListener.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.o -c /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/Listener/IEventListener.cpp

CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/Listener/IEventListener.cpp > CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.i

CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/Listener/IEventListener.cpp -o CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.s

CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.o: CMakeFiles/BatNavProject.dir/flags.make
CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.o: ../Engine/Event/Listener/EventListener.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.o -c /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/Listener/EventListener.cpp

CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/Listener/EventListener.cpp > CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.i

CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/Listener/EventListener.cpp -o CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.s

CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.o: CMakeFiles/BatNavProject.dir/flags.make
CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.o: ../Engine/Event/EventTypes/Event.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.o -c /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/EventTypes/Event.cpp

CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/EventTypes/Event.cpp > CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.i

CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/EventTypes/Event.cpp -o CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.s

CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.o: CMakeFiles/BatNavProject.dir/flags.make
CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.o: ../Engine/Event/EventTypes/ClickEvent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.o -c /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/EventTypes/ClickEvent.cpp

CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/EventTypes/ClickEvent.cpp > CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.i

CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/Engine/Event/EventTypes/ClickEvent.cpp -o CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.s

# Object files for target BatNavProject
BatNavProject_OBJECTS = \
"CMakeFiles/BatNavProject.dir/main.cpp.o" \
"CMakeFiles/BatNavProject.dir/Engine/Game.cpp.o" \
"CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.o" \
"CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.o" \
"CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.o" \
"CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.o" \
"CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.o" \
"CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.o" \
"CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.o" \
"CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.o"

# External object files for target BatNavProject
BatNavProject_EXTERNAL_OBJECTS =

BatNavProject: CMakeFiles/BatNavProject.dir/main.cpp.o
BatNavProject: CMakeFiles/BatNavProject.dir/Engine/Game.cpp.o
BatNavProject: CMakeFiles/BatNavProject.dir/Gameplay/GameManager.cpp.o
BatNavProject: CMakeFiles/BatNavProject.dir/Gameplay/Board/Board.cpp.o
BatNavProject: CMakeFiles/BatNavProject.dir/Engine/Input/InputManager.cpp.o
BatNavProject: CMakeFiles/BatNavProject.dir/Engine/Event/EventManager.cpp.o
BatNavProject: CMakeFiles/BatNavProject.dir/Engine/Event/Listener/IEventListener.cpp.o
BatNavProject: CMakeFiles/BatNavProject.dir/Engine/Event/Listener/EventListener.cpp.o
BatNavProject: CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/Event.cpp.o
BatNavProject: CMakeFiles/BatNavProject.dir/Engine/Event/EventTypes/ClickEvent.cpp.o
BatNavProject: CMakeFiles/BatNavProject.dir/build.make
BatNavProject: /usr/local/lib/libsfml-graphics.2.5.1.dylib
BatNavProject: /usr/local/lib/libsfml-audio.2.5.1.dylib
BatNavProject: /usr/local/lib/libsfml-network.2.5.1.dylib
BatNavProject: /usr/local/lib/libsfml-window.2.5.1.dylib
BatNavProject: /usr/local/lib/libsfml-system.2.5.1.dylib
BatNavProject: CMakeFiles/BatNavProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable BatNavProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BatNavProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BatNavProject.dir/build: BatNavProject

.PHONY : CMakeFiles/BatNavProject.dir/build

CMakeFiles/BatNavProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BatNavProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BatNavProject.dir/clean

CMakeFiles/BatNavProject.dir/depend:
	cd /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug /Users/cha/Desktop/dev/cpp/SFML/BatNav/BatNavProject/cmake-build-debug/CMakeFiles/BatNavProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BatNavProject.dir/depend

