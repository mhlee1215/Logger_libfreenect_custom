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
include wrappers/opencv/CMakeFiles/freenect_cv.dir/depend.make

# Include the progress variables for this target.
include wrappers/opencv/CMakeFiles/freenect_cv.dir/progress.make

# Include the compile flags for this target's objects.
include wrappers/opencv/CMakeFiles/freenect_cv.dir/flags.make

wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o: wrappers/opencv/CMakeFiles/freenect_cv.dir/flags.make
wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o: wrappers/opencv/libfreenect_cv.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mhlee/Downloads/Logger_libfreenect_custom/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o"
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o   -c /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv/libfreenect_cv.c

wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freenect_cv.dir/libfreenect_cv.c.i"
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv/libfreenect_cv.c > CMakeFiles/freenect_cv.dir/libfreenect_cv.c.i

wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freenect_cv.dir/libfreenect_cv.c.s"
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv/libfreenect_cv.c -o CMakeFiles/freenect_cv.dir/libfreenect_cv.c.s

wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o.requires:
.PHONY : wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o.requires

wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o.provides: wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o.requires
	$(MAKE) -f wrappers/opencv/CMakeFiles/freenect_cv.dir/build.make wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o.provides.build
.PHONY : wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o.provides

wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o.provides.build: wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o

# Object files for target freenect_cv
freenect_cv_OBJECTS = \
"CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o"

# External object files for target freenect_cv
freenect_cv_EXTERNAL_OBJECTS =

lib/libfreenect_cv.so.0.5.3: wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o
lib/libfreenect_cv.so.0.5.3: wrappers/opencv/CMakeFiles/freenect_cv.dir/build.make
lib/libfreenect_cv.so.0.5.3: lib/libfreenect_sync.so.0.5.3
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libboost_filesystem.a
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libboost_system.a
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libboost_thread.a
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libz.so
lib/libfreenect_cv.so.0.5.3: lib/libfreenect.so.0.5.3
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
lib/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
lib/libfreenect_cv.so.0.5.3: wrappers/opencv/CMakeFiles/freenect_cv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../lib/libfreenect_cv.so"
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freenect_cv.dir/link.txt --verbose=$(VERBOSE)
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && $(CMAKE_COMMAND) -E cmake_symlink_library ../../lib/libfreenect_cv.so.0.5.3 ../../lib/libfreenect_cv.so.0.5 ../../lib/libfreenect_cv.so

lib/libfreenect_cv.so.0.5: lib/libfreenect_cv.so.0.5.3

lib/libfreenect_cv.so: lib/libfreenect_cv.so.0.5.3

# Rule to build all files generated by this target.
wrappers/opencv/CMakeFiles/freenect_cv.dir/build: lib/libfreenect_cv.so
.PHONY : wrappers/opencv/CMakeFiles/freenect_cv.dir/build

# Object files for target freenect_cv
freenect_cv_OBJECTS = \
"CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o"

# External object files for target freenect_cv
freenect_cv_EXTERNAL_OBJECTS =

wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: wrappers/opencv/CMakeFiles/freenect_cv.dir/build.make
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: lib/libfreenect_sync.so.0.5.3
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libboost_filesystem.a
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libboost_system.a
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libboost_thread.a
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libz.so
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: lib/libfreenect.so.0.5.3
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3: wrappers/opencv/CMakeFiles/freenect_cv.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library CMakeFiles/CMakeRelink.dir/libfreenect_cv.so"
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freenect_cv.dir/relink.txt --verbose=$(VERBOSE)
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && $(CMAKE_COMMAND) -E cmake_symlink_library CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3 CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5 CMakeFiles/CMakeRelink.dir/libfreenect_cv.so

wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5: wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3

wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so: wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so.0.5.3

# Rule to relink during preinstall.
wrappers/opencv/CMakeFiles/freenect_cv.dir/preinstall: wrappers/opencv/CMakeFiles/CMakeRelink.dir/libfreenect_cv.so
.PHONY : wrappers/opencv/CMakeFiles/freenect_cv.dir/preinstall

wrappers/opencv/CMakeFiles/freenect_cv.dir/requires: wrappers/opencv/CMakeFiles/freenect_cv.dir/libfreenect_cv.c.o.requires
.PHONY : wrappers/opencv/CMakeFiles/freenect_cv.dir/requires

wrappers/opencv/CMakeFiles/freenect_cv.dir/clean:
	cd /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv && $(CMAKE_COMMAND) -P CMakeFiles/freenect_cv.dir/cmake_clean.cmake
.PHONY : wrappers/opencv/CMakeFiles/freenect_cv.dir/clean

wrappers/opencv/CMakeFiles/freenect_cv.dir/depend:
	cd /home/mhlee/Downloads/Logger_libfreenect_custom && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mhlee/Downloads/Logger_libfreenect_custom /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv /home/mhlee/Downloads/Logger_libfreenect_custom /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv /home/mhlee/Downloads/Logger_libfreenect_custom/wrappers/opencv/CMakeFiles/freenect_cv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : wrappers/opencv/CMakeFiles/freenect_cv.dir/depend

