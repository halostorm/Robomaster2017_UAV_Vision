# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/Flight2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/Flight2/build

# Include any dependencies generated for this target.
include CMakeFiles/aka.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/aka.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/aka.dir/flags.make

CMakeFiles/aka.dir/main.cpp.o: CMakeFiles/aka.dir/flags.make
CMakeFiles/aka.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Flight2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/aka.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aka.dir/main.cpp.o -c /home/ubuntu/Flight2/main.cpp

CMakeFiles/aka.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aka.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Flight2/main.cpp > CMakeFiles/aka.dir/main.cpp.i

CMakeFiles/aka.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aka.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Flight2/main.cpp -o CMakeFiles/aka.dir/main.cpp.s

CMakeFiles/aka.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/aka.dir/main.cpp.o.requires

CMakeFiles/aka.dir/main.cpp.o.provides: CMakeFiles/aka.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/aka.dir/build.make CMakeFiles/aka.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/aka.dir/main.cpp.o.provides

CMakeFiles/aka.dir/main.cpp.o.provides.build: CMakeFiles/aka.dir/main.cpp.o


# Object files for target aka
aka_OBJECTS = \
"CMakeFiles/aka.dir/main.cpp.o"

# External object files for target aka
aka_EXTERNAL_OBJECTS =

aka: CMakeFiles/aka.dir/main.cpp.o
aka: CMakeFiles/aka.dir/build.make
aka: /usr/local/lib/libopencv_videostab.so.3.1.0
aka: /usr/local/lib/libopencv_superres.so.3.1.0
aka: /usr/local/lib/libopencv_stitching.so.3.1.0
aka: /usr/local/lib/libopencv_shape.so.3.1.0
aka: /usr/local/lib/libopencv_photo.so.3.1.0
aka: /usr/local/lib/libopencv_cudastereo.so.3.1.0
aka: /usr/local/lib/libopencv_cudaoptflow.so.3.1.0
aka: /usr/local/lib/libopencv_cudaobjdetect.so.3.1.0
aka: /usr/local/lib/libopencv_cudalegacy.so.3.1.0
aka: /usr/local/lib/libopencv_cudaimgproc.so.3.1.0
aka: /usr/local/lib/libopencv_cudafeatures2d.so.3.1.0
aka: /usr/local/lib/libopencv_cudacodec.so.3.1.0
aka: /usr/local/lib/libopencv_cudabgsegm.so.3.1.0
aka: /usr/local/lib/libopencv_calib3d.so.3.1.0
aka: /usr/local/lib/libopencv_cudawarping.so.3.1.0
aka: /usr/local/lib/libopencv_objdetect.so.3.1.0
aka: /usr/local/lib/libopencv_cudafilters.so.3.1.0
aka: /usr/local/lib/libopencv_cudaarithm.so.3.1.0
aka: /usr/local/lib/libopencv_features2d.so.3.1.0
aka: /usr/local/lib/libopencv_ml.so.3.1.0
aka: /usr/local/lib/libopencv_highgui.so.3.1.0
aka: /usr/local/lib/libopencv_videoio.so.3.1.0
aka: /usr/local/lib/libopencv_imgcodecs.so.3.1.0
aka: /usr/local/lib/libopencv_flann.so.3.1.0
aka: /usr/local/lib/libopencv_video.so.3.1.0
aka: /usr/local/lib/libopencv_imgproc.so.3.1.0
aka: /usr/local/lib/libopencv_core.so.3.1.0
aka: /usr/local/lib/libopencv_cudev.so.3.1.0
aka: CMakeFiles/aka.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/Flight2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable aka"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aka.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/aka.dir/build: aka

.PHONY : CMakeFiles/aka.dir/build

CMakeFiles/aka.dir/requires: CMakeFiles/aka.dir/main.cpp.o.requires

.PHONY : CMakeFiles/aka.dir/requires

CMakeFiles/aka.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/aka.dir/cmake_clean.cmake
.PHONY : CMakeFiles/aka.dir/clean

CMakeFiles/aka.dir/depend:
	cd /home/ubuntu/Flight2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/Flight2 /home/ubuntu/Flight2 /home/ubuntu/Flight2/build /home/ubuntu/Flight2/build /home/ubuntu/Flight2/build/CMakeFiles/aka.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/aka.dir/depend

