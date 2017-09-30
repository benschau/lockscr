cmake_minimum_required(VERSION 3.3)

project(LockScr)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules")
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(Cairo)
find_package(cairo-xcb)
find_package(xcb)
find_package(xcb-ewmh)

if (CAIRO_FOUND) 
    MESSAGE("LOG: Cairo library found OK.")
    MESSAGE("\t${CAIRO_INCLUDE_DIRS}\n")
    MESSAGE("\t${CAIRO_LIBRARIES}")
endif ()
 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CAIRO_INCLUDE_DIRS})
include_directories(${CAIRO_LIBRARIES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)


