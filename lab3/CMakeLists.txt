cmake_minimum_required(VERSION 3.5)
project(lab3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package( OpenCV REQUIRED )

set(SOURCE_FILES main.cpp)
add_executable(lab3 ${SOURCE_FILES})
include_directories(include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(lab3 ${OpenCV_LIBS})
