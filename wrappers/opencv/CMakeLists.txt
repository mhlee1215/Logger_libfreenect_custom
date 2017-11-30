######################################################################################
# OpenCV Interface
######################################################################################
find_package(OpenCV REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Boost REQUIRED)
set(BOOST_LIBRARYDIR ${Boost_LIBRARIES})
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS date_time)


add_library (freenect_cv SHARED libfreenect_cv.c)
set_target_properties (freenect_cv PROPERTIES
  VERSION ${PROJECT_VER}
  SOVERSION ${PROJECT_APIVER})

include_directories (../c_sync)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${BOOST_LIBRARYDIR})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})


find_package(Boost COMPONENTS filesystem)
set(Boost_filesystem_lib ${Boost_LIBRARIES})
find_package(Boost COMPONENTS system)
set(Boost_system_lib ${Boost_LIBRARIES})
find_package(Boost COMPONENTS thread REQUIRED)


target_link_libraries (freenect_cv freenect_sync 
#                ${OPENGL_LIBRARIES} 
#                ${GLUT_LIBRARY} 
#                ${CMAKE_THREAD_LIBS_INIT} 
#                ${MATH_LIB}
                ${BOOST_LIBRARYDIR}
                ${Boost_filesystem_lib}
                ${Boost_system_lib}
                ${Boost_THREAD_LIBRARY}
                ${OpenCV_LIBS}
                ${ZLIB_LIBRARY}
        )


install (TARGETS freenect_cv
  DESTINATION "${PROJECT_LIBRARY_INSTALL_DIR}")
install (FILES "libfreenect_cv.h"
  DESTINATION ${PROJECT_INCLUDE_INSTALL_DIR})

add_executable(freenect-cvdemo cvdemo.cpp)
target_link_libraries(freenect-cvdemo freenect freenect_sync freenect_cv ${OpenCV_LIBS})
install (TARGETS freenect-cvdemo DESTINATION bin)

add_executable(freenect-cvdemo-multi cvdemo_multi.cpp)
target_link_libraries(freenect-cvdemo-multi freenect freenect_sync freenect_cv ${OpenCV_LIBS})
install (TARGETS freenect-cvdemo-multi DESTINATION bin)
