# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mhlee/Downloads/Logger_libfreenect_custom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mhlee/Downloads/Logger_libfreenect_custom

# Include any dependencies generated for this target.
include wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/depend.make

# Include the progress variables for this target.
include wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/progress.make

# Include the compile flags for this target's objects.
include wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/flags.make

wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o: wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/flags.make
wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o: wrappers/opencv/cvdemo_multi.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mhlee/Downloads/Logger_libfreenect_custom/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o"
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o -c /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv/cvdemo_multi.cpp

wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.i"
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv/cvdemo_multi.cpp > CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.i

wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.s"
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv/cvdemo_multi.cpp -o CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.s

wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o.requires:
.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o.requires

wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o.provides: wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o.requires
	$(MAKE) -f wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/build.make wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o.provides.build
.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o.provides

wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o.provides.build: wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o

# Object files for target freenect-cvdemo-multi
freenect__cvdemo__multi_OBJECTS = \
"CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o"

# External object files for target freenect-cvdemo-multi
freenect__cvdemo__multi_EXTERNAL_OBJECTS =

bin/freenect-cvdemo-multi: wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o
bin/freenect-cvdemo-multi: wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/build.make
bin/freenect-cvdemo-multi: lib/libfreenect.so.0.5.3
bin/freenect-cvdemo-multi: lib/libfreenect_sync.so.0.5.3
bin/freenect-cvdemo-multi: lib/libfreenect_cv.so.0.5.3
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
bin/freenect-cvdemo-multi: lib/libfreenect_sync.so.0.5.3
bin/freenect-cvdemo-multi: lib/libfreenect.so.0.5.3
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libboost_filesystem.a
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libboost_system.a
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libboost_thread.a
bin/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libz.so
bin/freenect-cvdemo-multi: wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/freenect-cvdemo-multi"
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freenect-cvdemo-multi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/build: bin/freenect-cvdemo-multi
.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/build

# Object files for target freenect-cvdemo-multi
freenect__cvdemo__multi_OBJECTS = \
"CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o"

# External object files for target freenect-cvdemo-multi
freenect__cvdemo__multi_EXTERNAL_OBJECTS =

wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/build.make
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: lib/libfreenect.so.0.5.3
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: lib/libfreenect_sync.so.0.5.3
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: lib/libfreenect_cv.so.0.5.3
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: lib/libfreenect_sync.so.0.5.3
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: lib/libfreenect.so.0.5.3
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libboost_filesystem.a
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libboost_system.a
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libboost_thread.a
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: /usr/lib/x86_64-linux-gnu/libz.so
wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi: wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi"
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freenect-cvdemo-multi.dir/relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/preinstall: wrappers/opencv/CMakeFiles/CMakeRelink.dir/freenect-cvdemo-multi
.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/preinstall

wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/requires: wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/cvdemo_multi.cpp.o.requires
.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/requires

wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/clean:
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && $(CMAKE_COMMAND) -P CMakeFiles/freenect-cvdemo-multi.dir/cmake_clean.cmake
.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/clean

wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/depend:
	cd /home/mhlee/Downloads/Logger_libfreenect_custom && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mhlee/Downloads/Logger_libfreenect_custom /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv /home/mhlee/Downloads/Logger_libfreenect_custom /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : wrappers/opencv/CMakeFiles/freenect-cvdemo-multi.dir/depend
