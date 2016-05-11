# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.4.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.4.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mhlee/Downloads/libfreenect_custom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mhlee/Downloads/libfreenect_custom

# Include any dependencies generated for this target.
include wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/depend.make

# Include the progress variables for this target.
include wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/progress.make

# Include the compile flags for this target's objects.
include wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/flags.make

wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o: wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/flags.make
wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o: wrappers/opencv/cvdemo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mhlee/Downloads/libfreenect_custom/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o"
	cd /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o   -c /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv/cvdemo.c

wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect-cvdemo.dir/cvdemo.c.i"
	cd /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv/cvdemo.c > CMakeFiles/freenect-cvdemo.dir/cvdemo.c.i

wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect-cvdemo.dir/cvdemo.c.s"
	cd /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv/cvdemo.c -o CMakeFiles/freenect-cvdemo.dir/cvdemo.c.s

wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o.requires:

.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o.requires

wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o.provides: wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o.requires
	$(MAKE) -f wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/build.make wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o.provides.build
.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o.provides

wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o.provides.build: wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o


# Object files for target freenect-cvdemo
freenect__cvdemo_OBJECTS = \
"CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o"

# External object files for target freenect-cvdemo
freenect__cvdemo_EXTERNAL_OBJECTS =

bin/freenect-cvdemo: wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o
bin/freenect-cvdemo: wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/build.make
bin/freenect-cvdemo: lib/libfreenect_cv.0.5.3.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_videostab.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_ts.a
bin/freenect-cvdemo: /usr/local/lib/libopencv_superres.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_stitching.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_contrib.2.4.12.dylib
bin/freenect-cvdemo: lib/libfreenect_sync.0.5.3.dylib
bin/freenect-cvdemo: lib/libfreenect.0.5.3.dylib
bin/freenect-cvdemo: /opt/local/lib/libusb-1.0.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_nonfree.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_ocl.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_gpu.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_photo.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_objdetect.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_legacy.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_video.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_ml.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_calib3d.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_features2d.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_highgui.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_imgproc.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_flann.2.4.12.dylib
bin/freenect-cvdemo: /usr/local/lib/libopencv_core.2.4.12.dylib
bin/freenect-cvdemo: wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mhlee/Downloads/libfreenect_custom/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/freenect-cvdemo"
	cd /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freenect-cvdemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/build: bin/freenect-cvdemo

.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/build

wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/requires: wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/cvdemo.c.o.requires

.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/requires

wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/clean:
	cd /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv && $(CMAKE_COMMAND) -P CMakeFiles/freenect-cvdemo.dir/cmake_clean.cmake
.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/clean

wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/depend:
	cd /Users/mhlee/Downloads/libfreenect_custom && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mhlee/Downloads/libfreenect_custom /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv /Users/mhlee/Downloads/libfreenect_custom /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo.dir/depend

