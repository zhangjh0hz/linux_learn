# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/zhangjh/Downloads/clion-2018.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/zhangjh/Downloads/clion-2018.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhangjh/workspace/linux_test/net

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhangjh/workspace/linux_test/net/cmake-build-debug

# Include any dependencies generated for this target.
include poll/CMakeFiles/poll_svr.dir/depend.make

# Include the progress variables for this target.
include poll/CMakeFiles/poll_svr.dir/progress.make

# Include the compile flags for this target's objects.
include poll/CMakeFiles/poll_svr.dir/flags.make

poll/CMakeFiles/poll_svr.dir/poll_svr.c.o: poll/CMakeFiles/poll_svr.dir/flags.make
poll/CMakeFiles/poll_svr.dir/poll_svr.c.o: ../poll/poll_svr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhangjh/workspace/linux_test/net/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object poll/CMakeFiles/poll_svr.dir/poll_svr.c.o"
	cd /home/zhangjh/workspace/linux_test/net/cmake-build-debug/poll && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/poll_svr.dir/poll_svr.c.o   -c /home/zhangjh/workspace/linux_test/net/poll/poll_svr.c

poll/CMakeFiles/poll_svr.dir/poll_svr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/poll_svr.dir/poll_svr.c.i"
	cd /home/zhangjh/workspace/linux_test/net/cmake-build-debug/poll && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zhangjh/workspace/linux_test/net/poll/poll_svr.c > CMakeFiles/poll_svr.dir/poll_svr.c.i

poll/CMakeFiles/poll_svr.dir/poll_svr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/poll_svr.dir/poll_svr.c.s"
	cd /home/zhangjh/workspace/linux_test/net/cmake-build-debug/poll && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zhangjh/workspace/linux_test/net/poll/poll_svr.c -o CMakeFiles/poll_svr.dir/poll_svr.c.s

# Object files for target poll_svr
poll_svr_OBJECTS = \
"CMakeFiles/poll_svr.dir/poll_svr.c.o"

# External object files for target poll_svr
poll_svr_EXTERNAL_OBJECTS =

bin/poll_svr: poll/CMakeFiles/poll_svr.dir/poll_svr.c.o
bin/poll_svr: poll/CMakeFiles/poll_svr.dir/build.make
bin/poll_svr: lib/libbase_sock.so
bin/poll_svr: poll/CMakeFiles/poll_svr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhangjh/workspace/linux_test/net/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/poll_svr"
	cd /home/zhangjh/workspace/linux_test/net/cmake-build-debug/poll && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/poll_svr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
poll/CMakeFiles/poll_svr.dir/build: bin/poll_svr

.PHONY : poll/CMakeFiles/poll_svr.dir/build

poll/CMakeFiles/poll_svr.dir/clean:
	cd /home/zhangjh/workspace/linux_test/net/cmake-build-debug/poll && $(CMAKE_COMMAND) -P CMakeFiles/poll_svr.dir/cmake_clean.cmake
.PHONY : poll/CMakeFiles/poll_svr.dir/clean

poll/CMakeFiles/poll_svr.dir/depend:
	cd /home/zhangjh/workspace/linux_test/net/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhangjh/workspace/linux_test/net /home/zhangjh/workspace/linux_test/net/poll /home/zhangjh/workspace/linux_test/net/cmake-build-debug /home/zhangjh/workspace/linux_test/net/cmake-build-debug/poll /home/zhangjh/workspace/linux_test/net/cmake-build-debug/poll/CMakeFiles/poll_svr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : poll/CMakeFiles/poll_svr.dir/depend
