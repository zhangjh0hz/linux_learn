# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/george/workspace/linux_learn/net

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/george/workspace/linux_learn/net/build

# Include any dependencies generated for this target.
include poll/CMakeFiles/poll_svr.dir/depend.make

# Include the progress variables for this target.
include poll/CMakeFiles/poll_svr.dir/progress.make

# Include the compile flags for this target's objects.
include poll/CMakeFiles/poll_svr.dir/flags.make

poll/CMakeFiles/poll_svr.dir/poll_svr.c.o: poll/CMakeFiles/poll_svr.dir/flags.make
poll/CMakeFiles/poll_svr.dir/poll_svr.c.o: ../poll/poll_svr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/george/workspace/linux_learn/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object poll/CMakeFiles/poll_svr.dir/poll_svr.c.o"
	cd /home/george/workspace/linux_learn/net/build/poll && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/poll_svr.dir/poll_svr.c.o   -c /home/george/workspace/linux_learn/net/poll/poll_svr.c

poll/CMakeFiles/poll_svr.dir/poll_svr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/poll_svr.dir/poll_svr.c.i"
	cd /home/george/workspace/linux_learn/net/build/poll && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/george/workspace/linux_learn/net/poll/poll_svr.c > CMakeFiles/poll_svr.dir/poll_svr.c.i

poll/CMakeFiles/poll_svr.dir/poll_svr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/poll_svr.dir/poll_svr.c.s"
	cd /home/george/workspace/linux_learn/net/build/poll && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/george/workspace/linux_learn/net/poll/poll_svr.c -o CMakeFiles/poll_svr.dir/poll_svr.c.s

poll/CMakeFiles/poll_svr.dir/poll_svr.c.o.requires:

.PHONY : poll/CMakeFiles/poll_svr.dir/poll_svr.c.o.requires

poll/CMakeFiles/poll_svr.dir/poll_svr.c.o.provides: poll/CMakeFiles/poll_svr.dir/poll_svr.c.o.requires
	$(MAKE) -f poll/CMakeFiles/poll_svr.dir/build.make poll/CMakeFiles/poll_svr.dir/poll_svr.c.o.provides.build
.PHONY : poll/CMakeFiles/poll_svr.dir/poll_svr.c.o.provides

poll/CMakeFiles/poll_svr.dir/poll_svr.c.o.provides.build: poll/CMakeFiles/poll_svr.dir/poll_svr.c.o


# Object files for target poll_svr
poll_svr_OBJECTS = \
"CMakeFiles/poll_svr.dir/poll_svr.c.o"

# External object files for target poll_svr
poll_svr_EXTERNAL_OBJECTS =

bin/poll_svr: poll/CMakeFiles/poll_svr.dir/poll_svr.c.o
bin/poll_svr: poll/CMakeFiles/poll_svr.dir/build.make
bin/poll_svr: lib/libbase_sock.so
bin/poll_svr: poll/CMakeFiles/poll_svr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/george/workspace/linux_learn/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/poll_svr"
	cd /home/george/workspace/linux_learn/net/build/poll && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/poll_svr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
poll/CMakeFiles/poll_svr.dir/build: bin/poll_svr

.PHONY : poll/CMakeFiles/poll_svr.dir/build

poll/CMakeFiles/poll_svr.dir/requires: poll/CMakeFiles/poll_svr.dir/poll_svr.c.o.requires

.PHONY : poll/CMakeFiles/poll_svr.dir/requires

poll/CMakeFiles/poll_svr.dir/clean:
	cd /home/george/workspace/linux_learn/net/build/poll && $(CMAKE_COMMAND) -P CMakeFiles/poll_svr.dir/cmake_clean.cmake
.PHONY : poll/CMakeFiles/poll_svr.dir/clean

poll/CMakeFiles/poll_svr.dir/depend:
	cd /home/george/workspace/linux_learn/net/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/george/workspace/linux_learn/net /home/george/workspace/linux_learn/net/poll /home/george/workspace/linux_learn/net/build /home/george/workspace/linux_learn/net/build/poll /home/george/workspace/linux_learn/net/build/poll/CMakeFiles/poll_svr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : poll/CMakeFiles/poll_svr.dir/depend

