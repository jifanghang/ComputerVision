cmake_minimum_required(VERSION 3.6)
project(donald)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lab_homography_donald.cpp)
add_executable(donald ${SOURCE_FILES})

find_package( OpenCV REQUIRED )
include_directories( include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(donald ${OpenCV_LIBS})