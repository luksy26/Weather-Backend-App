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
CMAKE_SOURCE_DIR = /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/build

# Include any dependencies generated for this target.
include CMakeFiles/WeatherApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/WeatherApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/WeatherApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WeatherApp.dir/flags.make

CMakeFiles/WeatherApp.dir/WeatherServer.cpp.o: CMakeFiles/WeatherApp.dir/flags.make
CMakeFiles/WeatherApp.dir/WeatherServer.cpp.o: ../WeatherServer.cpp
CMakeFiles/WeatherApp.dir/WeatherServer.cpp.o: CMakeFiles/WeatherApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WeatherApp.dir/WeatherServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WeatherApp.dir/WeatherServer.cpp.o -MF CMakeFiles/WeatherApp.dir/WeatherServer.cpp.o.d -o CMakeFiles/WeatherApp.dir/WeatherServer.cpp.o -c /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/WeatherServer.cpp

CMakeFiles/WeatherApp.dir/WeatherServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WeatherApp.dir/WeatherServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/WeatherServer.cpp > CMakeFiles/WeatherApp.dir/WeatherServer.cpp.i

CMakeFiles/WeatherApp.dir/WeatherServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WeatherApp.dir/WeatherServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/WeatherServer.cpp -o CMakeFiles/WeatherApp.dir/WeatherServer.cpp.s

CMakeFiles/WeatherApp.dir/WeatherClient.cpp.o: CMakeFiles/WeatherApp.dir/flags.make
CMakeFiles/WeatherApp.dir/WeatherClient.cpp.o: ../WeatherClient.cpp
CMakeFiles/WeatherApp.dir/WeatherClient.cpp.o: CMakeFiles/WeatherApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/WeatherApp.dir/WeatherClient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WeatherApp.dir/WeatherClient.cpp.o -MF CMakeFiles/WeatherApp.dir/WeatherClient.cpp.o.d -o CMakeFiles/WeatherApp.dir/WeatherClient.cpp.o -c /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/WeatherClient.cpp

CMakeFiles/WeatherApp.dir/WeatherClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WeatherApp.dir/WeatherClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/WeatherClient.cpp > CMakeFiles/WeatherApp.dir/WeatherClient.cpp.i

CMakeFiles/WeatherApp.dir/WeatherClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WeatherApp.dir/WeatherClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/WeatherClient.cpp -o CMakeFiles/WeatherApp.dir/WeatherClient.cpp.s

CMakeFiles/WeatherApp.dir/main.cpp.o: CMakeFiles/WeatherApp.dir/flags.make
CMakeFiles/WeatherApp.dir/main.cpp.o: ../main.cpp
CMakeFiles/WeatherApp.dir/main.cpp.o: CMakeFiles/WeatherApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/WeatherApp.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WeatherApp.dir/main.cpp.o -MF CMakeFiles/WeatherApp.dir/main.cpp.o.d -o CMakeFiles/WeatherApp.dir/main.cpp.o -c /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/main.cpp

CMakeFiles/WeatherApp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WeatherApp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/main.cpp > CMakeFiles/WeatherApp.dir/main.cpp.i

CMakeFiles/WeatherApp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WeatherApp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/main.cpp -o CMakeFiles/WeatherApp.dir/main.cpp.s

# Object files for target WeatherApp
WeatherApp_OBJECTS = \
"CMakeFiles/WeatherApp.dir/WeatherServer.cpp.o" \
"CMakeFiles/WeatherApp.dir/WeatherClient.cpp.o" \
"CMakeFiles/WeatherApp.dir/main.cpp.o"

# External object files for target WeatherApp
WeatherApp_EXTERNAL_OBJECTS =

WeatherApp: CMakeFiles/WeatherApp.dir/WeatherServer.cpp.o
WeatherApp: CMakeFiles/WeatherApp.dir/WeatherClient.cpp.o
WeatherApp: CMakeFiles/WeatherApp.dir/main.cpp.o
WeatherApp: CMakeFiles/WeatherApp.dir/build.make
WeatherApp: CMakeFiles/WeatherApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable WeatherApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WeatherApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WeatherApp.dir/build: WeatherApp
.PHONY : CMakeFiles/WeatherApp.dir/build

CMakeFiles/WeatherApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WeatherApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WeatherApp.dir/clean

CMakeFiles/WeatherApp.dir/depend:
	cd /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/build /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/build /mnt/c/Users/Lucas/OneDrive/Desktop/master/SASPS/proj/Weather-Backend-App/build/CMakeFiles/WeatherApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WeatherApp.dir/depend

