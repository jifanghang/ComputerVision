cmake_minimum_required(VERSION 3.5)
project(lab4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( OpenCV REQUIRED )
find_package( Boost REQUIRED COMPONENTS system filesystem )

include_directories( include ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})  #${Eigen_INCLUDE_DIRS}

set(SOURCE_FILES facerec_eigenfaces.cpp)
add_executable(lab4 ${SOURCE_FILES})

target_link_libraries(lab4 ${OpenCV_LIBS} ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY})