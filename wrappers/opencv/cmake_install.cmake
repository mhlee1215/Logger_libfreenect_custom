# Install script for directory: /Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/mhlee/Downloads/libfreenect_custom/lib/libfreenect_cv.0.5.3.dylib"
    "/Users/mhlee/Downloads/libfreenect_custom/lib/libfreenect_cv.0.5.dylib"
    "/Users/mhlee/Downloads/libfreenect_custom/lib/libfreenect_cv.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libfreenect_cv.0.5.3.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libfreenect_cv.0.5.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libfreenect_cv.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "libfreenect_cv.0.5.dylib"
        -change "/Users/mhlee/Downloads/libfreenect_custom/lib/libfreenect.0.5.dylib" "libfreenect.0.5.dylib"
        -change "/Users/mhlee/Downloads/libfreenect_custom/lib/libfreenect_sync.0.5.dylib" "libfreenect_sync.0.5.dylib"
        "${file}")
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libfreenect" TYPE FILE FILES "/Users/mhlee/Downloads/libfreenect_custom/wrappers/opencv/libfreenect_cv.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/mhlee/Downloads/libfreenect_custom/bin/freenect-cvdemo")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/freenect-cvdemo" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/freenect-cvdemo")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "/Users/mhlee/Downloads/libfreenect_custom/lib/libfreenect.0.5.dylib" "libfreenect.0.5.dylib"
      -change "/Users/mhlee/Downloads/libfreenect_custom/lib/libfreenect_cv.0.5.dylib" "libfreenect_cv.0.5.dylib"
      -change "/Users/mhlee/Downloads/libfreenect_custom/lib/libfreenect_sync.0.5.dylib" "libfreenect_sync.0.5.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/freenect-cvdemo")
  endif()
endif()

