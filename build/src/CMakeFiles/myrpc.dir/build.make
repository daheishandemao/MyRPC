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
CMAKE_SOURCE_DIR = /home/ubuntu/zrx/projects/MyRPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/zrx/projects/MyRPC/build

# Include any dependencies generated for this target.
include src/CMakeFiles/myrpc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/myrpc.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/myrpc.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/myrpc.dir/flags.make

src/CMakeFiles/myrpc.dir/myrpcapplication.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/myrpcapplication.cc.o: ../src/myrpcapplication.cc
src/CMakeFiles/myrpc.dir/myrpcapplication.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/myrpc.dir/myrpcapplication.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/myrpcapplication.cc.o -MF CMakeFiles/myrpc.dir/myrpcapplication.cc.o.d -o CMakeFiles/myrpc.dir/myrpcapplication.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/myrpcapplication.cc

src/CMakeFiles/myrpc.dir/myrpcapplication.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/myrpcapplication.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/myrpcapplication.cc > CMakeFiles/myrpc.dir/myrpcapplication.cc.i

src/CMakeFiles/myrpc.dir/myrpcapplication.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/myrpcapplication.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/myrpcapplication.cc -o CMakeFiles/myrpc.dir/myrpcapplication.cc.s

src/CMakeFiles/myrpc.dir/myrpcconfig.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/myrpcconfig.cc.o: ../src/myrpcconfig.cc
src/CMakeFiles/myrpc.dir/myrpcconfig.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/myrpc.dir/myrpcconfig.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/myrpcconfig.cc.o -MF CMakeFiles/myrpc.dir/myrpcconfig.cc.o.d -o CMakeFiles/myrpc.dir/myrpcconfig.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/myrpcconfig.cc

src/CMakeFiles/myrpc.dir/myrpcconfig.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/myrpcconfig.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/myrpcconfig.cc > CMakeFiles/myrpc.dir/myrpcconfig.cc.i

src/CMakeFiles/myrpc.dir/myrpcconfig.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/myrpcconfig.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/myrpcconfig.cc -o CMakeFiles/myrpc.dir/myrpcconfig.cc.s

src/CMakeFiles/myrpc.dir/rpcprovider.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/rpcprovider.cc.o: ../src/rpcprovider.cc
src/CMakeFiles/myrpc.dir/rpcprovider.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/myrpc.dir/rpcprovider.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/rpcprovider.cc.o -MF CMakeFiles/myrpc.dir/rpcprovider.cc.o.d -o CMakeFiles/myrpc.dir/rpcprovider.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/rpcprovider.cc

src/CMakeFiles/myrpc.dir/rpcprovider.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/rpcprovider.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/rpcprovider.cc > CMakeFiles/myrpc.dir/rpcprovider.cc.i

src/CMakeFiles/myrpc.dir/rpcprovider.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/rpcprovider.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/rpcprovider.cc -o CMakeFiles/myrpc.dir/rpcprovider.cc.s

src/CMakeFiles/myrpc.dir/rpcheader.pb.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/rpcheader.pb.cc.o: ../src/rpcheader.pb.cc
src/CMakeFiles/myrpc.dir/rpcheader.pb.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/myrpc.dir/rpcheader.pb.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/rpcheader.pb.cc.o -MF CMakeFiles/myrpc.dir/rpcheader.pb.cc.o.d -o CMakeFiles/myrpc.dir/rpcheader.pb.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/rpcheader.pb.cc

src/CMakeFiles/myrpc.dir/rpcheader.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/rpcheader.pb.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/rpcheader.pb.cc > CMakeFiles/myrpc.dir/rpcheader.pb.cc.i

src/CMakeFiles/myrpc.dir/rpcheader.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/rpcheader.pb.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/rpcheader.pb.cc -o CMakeFiles/myrpc.dir/rpcheader.pb.cc.s

src/CMakeFiles/myrpc.dir/myrpcchannel.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/myrpcchannel.cc.o: ../src/myrpcchannel.cc
src/CMakeFiles/myrpc.dir/myrpcchannel.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/myrpc.dir/myrpcchannel.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/myrpcchannel.cc.o -MF CMakeFiles/myrpc.dir/myrpcchannel.cc.o.d -o CMakeFiles/myrpc.dir/myrpcchannel.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/myrpcchannel.cc

src/CMakeFiles/myrpc.dir/myrpcchannel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/myrpcchannel.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/myrpcchannel.cc > CMakeFiles/myrpc.dir/myrpcchannel.cc.i

src/CMakeFiles/myrpc.dir/myrpcchannel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/myrpcchannel.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/myrpcchannel.cc -o CMakeFiles/myrpc.dir/myrpcchannel.cc.s

src/CMakeFiles/myrpc.dir/myrpccontroller.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/myrpccontroller.cc.o: ../src/myrpccontroller.cc
src/CMakeFiles/myrpc.dir/myrpccontroller.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/myrpc.dir/myrpccontroller.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/myrpccontroller.cc.o -MF CMakeFiles/myrpc.dir/myrpccontroller.cc.o.d -o CMakeFiles/myrpc.dir/myrpccontroller.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/myrpccontroller.cc

src/CMakeFiles/myrpc.dir/myrpccontroller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/myrpccontroller.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/myrpccontroller.cc > CMakeFiles/myrpc.dir/myrpccontroller.cc.i

src/CMakeFiles/myrpc.dir/myrpccontroller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/myrpccontroller.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/myrpccontroller.cc -o CMakeFiles/myrpc.dir/myrpccontroller.cc.s

src/CMakeFiles/myrpc.dir/logger.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/logger.cc.o: ../src/logger.cc
src/CMakeFiles/myrpc.dir/logger.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/myrpc.dir/logger.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/logger.cc.o -MF CMakeFiles/myrpc.dir/logger.cc.o.d -o CMakeFiles/myrpc.dir/logger.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/logger.cc

src/CMakeFiles/myrpc.dir/logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/logger.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/logger.cc > CMakeFiles/myrpc.dir/logger.cc.i

src/CMakeFiles/myrpc.dir/logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/logger.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/logger.cc -o CMakeFiles/myrpc.dir/logger.cc.s

src/CMakeFiles/myrpc.dir/lockqueue.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/lockqueue.cc.o: ../src/lockqueue.cc
src/CMakeFiles/myrpc.dir/lockqueue.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/myrpc.dir/lockqueue.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/lockqueue.cc.o -MF CMakeFiles/myrpc.dir/lockqueue.cc.o.d -o CMakeFiles/myrpc.dir/lockqueue.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/lockqueue.cc

src/CMakeFiles/myrpc.dir/lockqueue.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/lockqueue.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/lockqueue.cc > CMakeFiles/myrpc.dir/lockqueue.cc.i

src/CMakeFiles/myrpc.dir/lockqueue.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/lockqueue.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/lockqueue.cc -o CMakeFiles/myrpc.dir/lockqueue.cc.s

src/CMakeFiles/myrpc.dir/zookeeperutil.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/zookeeperutil.cc.o: ../src/zookeeperutil.cc
src/CMakeFiles/myrpc.dir/zookeeperutil.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/myrpc.dir/zookeeperutil.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/zookeeperutil.cc.o -MF CMakeFiles/myrpc.dir/zookeeperutil.cc.o.d -o CMakeFiles/myrpc.dir/zookeeperutil.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/zookeeperutil.cc

src/CMakeFiles/myrpc.dir/zookeeperutil.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/zookeeperutil.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/zookeeperutil.cc > CMakeFiles/myrpc.dir/zookeeperutil.cc.i

src/CMakeFiles/myrpc.dir/zookeeperutil.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/zookeeperutil.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/zookeeperutil.cc -o CMakeFiles/myrpc.dir/zookeeperutil.cc.s

src/CMakeFiles/myrpc.dir/trace_context.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/trace_context.cc.o: ../src/trace_context.cc
src/CMakeFiles/myrpc.dir/trace_context.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/CMakeFiles/myrpc.dir/trace_context.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/trace_context.cc.o -MF CMakeFiles/myrpc.dir/trace_context.cc.o.d -o CMakeFiles/myrpc.dir/trace_context.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/trace_context.cc

src/CMakeFiles/myrpc.dir/trace_context.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/trace_context.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/trace_context.cc > CMakeFiles/myrpc.dir/trace_context.cc.i

src/CMakeFiles/myrpc.dir/trace_context.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/trace_context.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/trace_context.cc -o CMakeFiles/myrpc.dir/trace_context.cc.s

src/CMakeFiles/myrpc.dir/rate_limiter.cc.o: src/CMakeFiles/myrpc.dir/flags.make
src/CMakeFiles/myrpc.dir/rate_limiter.cc.o: ../src/rate_limiter.cc
src/CMakeFiles/myrpc.dir/rate_limiter.cc.o: src/CMakeFiles/myrpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/CMakeFiles/myrpc.dir/rate_limiter.cc.o"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/myrpc.dir/rate_limiter.cc.o -MF CMakeFiles/myrpc.dir/rate_limiter.cc.o.d -o CMakeFiles/myrpc.dir/rate_limiter.cc.o -c /home/ubuntu/zrx/projects/MyRPC/src/rate_limiter.cc

src/CMakeFiles/myrpc.dir/rate_limiter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrpc.dir/rate_limiter.cc.i"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/zrx/projects/MyRPC/src/rate_limiter.cc > CMakeFiles/myrpc.dir/rate_limiter.cc.i

src/CMakeFiles/myrpc.dir/rate_limiter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrpc.dir/rate_limiter.cc.s"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/zrx/projects/MyRPC/src/rate_limiter.cc -o CMakeFiles/myrpc.dir/rate_limiter.cc.s

# Object files for target myrpc
myrpc_OBJECTS = \
"CMakeFiles/myrpc.dir/myrpcapplication.cc.o" \
"CMakeFiles/myrpc.dir/myrpcconfig.cc.o" \
"CMakeFiles/myrpc.dir/rpcprovider.cc.o" \
"CMakeFiles/myrpc.dir/rpcheader.pb.cc.o" \
"CMakeFiles/myrpc.dir/myrpcchannel.cc.o" \
"CMakeFiles/myrpc.dir/myrpccontroller.cc.o" \
"CMakeFiles/myrpc.dir/logger.cc.o" \
"CMakeFiles/myrpc.dir/lockqueue.cc.o" \
"CMakeFiles/myrpc.dir/zookeeperutil.cc.o" \
"CMakeFiles/myrpc.dir/trace_context.cc.o" \
"CMakeFiles/myrpc.dir/rate_limiter.cc.o"

# External object files for target myrpc
myrpc_EXTERNAL_OBJECTS =

../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/myrpcapplication.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/myrpcconfig.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/rpcprovider.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/rpcheader.pb.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/myrpcchannel.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/myrpccontroller.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/logger.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/lockqueue.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/zookeeperutil.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/trace_context.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/rate_limiter.cc.o
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/build.make
../lib/libmyrpc.a: src/CMakeFiles/myrpc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/zrx/projects/MyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library ../../lib/libmyrpc.a"
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && $(CMAKE_COMMAND) -P CMakeFiles/myrpc.dir/cmake_clean_target.cmake
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myrpc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/myrpc.dir/build: ../lib/libmyrpc.a
.PHONY : src/CMakeFiles/myrpc.dir/build

src/CMakeFiles/myrpc.dir/clean:
	cd /home/ubuntu/zrx/projects/MyRPC/build/src && $(CMAKE_COMMAND) -P CMakeFiles/myrpc.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/myrpc.dir/clean

src/CMakeFiles/myrpc.dir/depend:
	cd /home/ubuntu/zrx/projects/MyRPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/zrx/projects/MyRPC /home/ubuntu/zrx/projects/MyRPC/src /home/ubuntu/zrx/projects/MyRPC/build /home/ubuntu/zrx/projects/MyRPC/build/src /home/ubuntu/zrx/projects/MyRPC/build/src/CMakeFiles/myrpc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/myrpc.dir/depend

