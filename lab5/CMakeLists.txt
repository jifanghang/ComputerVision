cmake_minimum_required(VERSION 3.5)
project(calibration)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES camera_calibration.cpp)
add_executable(calibration ${SOURCE_FILES})

find_package( OpenCV REQUIRED )
include_directories( include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(calibration ${OpenCV_LIBS})