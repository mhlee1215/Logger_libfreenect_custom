######################################################################################
# Packages needed for examples
######################################################################################

# These examples have no external dependencies and should always build.
#add_executable(freenect-camtest camtest.c)
#add_executable(freenect-wavrecord wavrecord.c)
#target_link_libraries(freenect-camtest freenect)
#target_link_libraries(freenect-wavrecord freenect)
#install(TARGETS freenect-camtest freenect-wavrecord
#        DESTINATION bin)

# All viewers need pthreads and GLUT.
set(THREADS_USE_PTHREADS_WIN32 true)
find_package(Threads)
find_package(OpenGL)
find_package(GLUT)
find_package(OpenCV REQUIRED)
find_package(ZLIB REQUIRED)

#boost
find_package(Boost REQUIRED)
set(BOOST_LIBRARYDIR ${Boost_LIBRARIES})
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS date_time)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${BOOST_LIBRARYDIR})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})

find_package(Boost COMPONENTS filesystem)
set(Boost_filesystem_lib ${Boost_LIBRARIES})
find_package(Boost COMPONENTS system)
set(Boost_system_lib ${Boost_LIBRARIES})
find_package(Boost COMPONENTS thread REQUIRED)


if (Threads_FOUND AND OPENGL_FOUND AND GLUT_FOUND)
  include_directories(${THREADS_PTHREADS_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

  #add_executable(freenect-glview glview.c)
  #add_executable(freenect-regview regview.cpp)
  add_executable(Logger regview.cpp)
 # add_executable(freenect-hiview hiview.c)
 # add_executable(freenect-chunkview chunkview.c)
 # add_executable(freenect-micview micview.c)

  #target_link_libraries(freenect-glview freenect ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIB})
  #target_link_libraries(freenect-regview freenect ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIB})
  
  MESSAGE(a ${BOOST_LIBRARYDIR})
  
  target_link_libraries(Logger freenect 
  		${OPENGL_LIBRARIES} 
  		${GLUT_LIBRARY} 
  		${CMAKE_THREAD_LIBS_INIT} 
  		${MATH_LIB}
  		${BOOST_LIBRARYDIR}
		${Boost_filesystem_lib}
		${Boost_system_lib}
		${Boost_THREAD_LIBRARY}
		${OpenCV_LIBS}
		${ZLIB_LIBRARY}
  	)
 # target_link_libraries(freenect-hiview freenect ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIB})
 # target_link_libraries(freenect-chunkview freenect ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIB})
 # target_link_libraries(freenect-micview freenect ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIB})

 install(TARGETS Logger DESTINATION bin)
  #install(TARGETS freenect-glview freenect-regview freenect-hiview freenect-chunkview freenect-micview
  #        DESTINATION bin)
        
endif ()

