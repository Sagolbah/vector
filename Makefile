# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /home/sagolbah/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4505.18/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/sagolbah/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4505.18/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sagolbah/SPbITMO/C++/homeworks/hw5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sagolbah/SPbITMO/C++/homeworks/hw5

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/sagolbah/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4505.18/bin/cmake/linux/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/home/sagolbah/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4505.18/bin/cmake/linux/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sagolbah/SPbITMO/C++/homeworks/hw5/CMakeFiles /home/sagolbah/SPbITMO/C++/homeworks/hw5/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sagolbah/SPbITMO/C++/homeworks/hw5/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named vector_testing

# Build rule for target.
vector_testing: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 vector_testing
.PHONY : vector_testing

# fast build rule for target.
vector_testing/fast:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/build
.PHONY : vector_testing/fast

counted.o: counted.cpp.o

.PHONY : counted.o

# target to build an object file
counted.cpp.o:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/counted.cpp.o
.PHONY : counted.cpp.o

counted.i: counted.cpp.i

.PHONY : counted.i

# target to preprocess a source file
counted.cpp.i:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/counted.cpp.i
.PHONY : counted.cpp.i

counted.s: counted.cpp.s

.PHONY : counted.s

# target to generate assembly for a file
counted.cpp.s:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/counted.cpp.s
.PHONY : counted.cpp.s

fault_injection.o: fault_injection.cpp.o

.PHONY : fault_injection.o

# target to build an object file
fault_injection.cpp.o:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/fault_injection.cpp.o
.PHONY : fault_injection.cpp.o

fault_injection.i: fault_injection.cpp.i

.PHONY : fault_injection.i

# target to preprocess a source file
fault_injection.cpp.i:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/fault_injection.cpp.i
.PHONY : fault_injection.cpp.i

fault_injection.s: fault_injection.cpp.s

.PHONY : fault_injection.s

# target to generate assembly for a file
fault_injection.cpp.s:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/fault_injection.cpp.s
.PHONY : fault_injection.cpp.s

gtest/gtest-all.o: gtest/gtest-all.cc.o

.PHONY : gtest/gtest-all.o

# target to build an object file
gtest/gtest-all.cc.o:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/gtest/gtest-all.cc.o
.PHONY : gtest/gtest-all.cc.o

gtest/gtest-all.i: gtest/gtest-all.cc.i

.PHONY : gtest/gtest-all.i

# target to preprocess a source file
gtest/gtest-all.cc.i:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/gtest/gtest-all.cc.i
.PHONY : gtest/gtest-all.cc.i

gtest/gtest-all.s: gtest/gtest-all.cc.s

.PHONY : gtest/gtest-all.s

# target to generate assembly for a file
gtest/gtest-all.cc.s:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/gtest/gtest-all.cc.s
.PHONY : gtest/gtest-all.cc.s

gtest/gtest_main.o: gtest/gtest_main.cc.o

.PHONY : gtest/gtest_main.o

# target to build an object file
gtest/gtest_main.cc.o:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/gtest/gtest_main.cc.o
.PHONY : gtest/gtest_main.cc.o

gtest/gtest_main.i: gtest/gtest_main.cc.i

.PHONY : gtest/gtest_main.i

# target to preprocess a source file
gtest/gtest_main.cc.i:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/gtest/gtest_main.cc.i
.PHONY : gtest/gtest_main.cc.i

gtest/gtest_main.s: gtest/gtest_main.cc.s

.PHONY : gtest/gtest_main.s

# target to generate assembly for a file
gtest/gtest_main.cc.s:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/gtest/gtest_main.cc.s
.PHONY : gtest/gtest_main.cc.s

vector_testing.o: vector_testing.cpp.o

.PHONY : vector_testing.o

# target to build an object file
vector_testing.cpp.o:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/vector_testing.cpp.o
.PHONY : vector_testing.cpp.o

vector_testing.i: vector_testing.cpp.i

.PHONY : vector_testing.i

# target to preprocess a source file
vector_testing.cpp.i:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/vector_testing.cpp.i
.PHONY : vector_testing.cpp.i

vector_testing.s: vector_testing.cpp.s

.PHONY : vector_testing.s

# target to generate assembly for a file
vector_testing.cpp.s:
	$(MAKE) -f CMakeFiles/vector_testing.dir/build.make CMakeFiles/vector_testing.dir/vector_testing.cpp.s
.PHONY : vector_testing.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... vector_testing"
	@echo "... counted.o"
	@echo "... counted.i"
	@echo "... counted.s"
	@echo "... fault_injection.o"
	@echo "... fault_injection.i"
	@echo "... fault_injection.s"
	@echo "... gtest/gtest-all.o"
	@echo "... gtest/gtest-all.i"
	@echo "... gtest/gtest-all.s"
	@echo "... gtest/gtest_main.o"
	@echo "... gtest/gtest_main.i"
	@echo "... gtest/gtest_main.s"
	@echo "... vector_testing.o"
	@echo "... vector_testing.i"
	@echo "... vector_testing.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

