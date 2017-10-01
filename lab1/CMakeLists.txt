cmake_minimum_required(VERSION 2.8)
project( hello_sunflowers )

find_package( OpenCV REQUIRED )

include_directories( include ${OpenCV_INCLUDE_DIRS} )

add_executable( hello_sunflowers 
 src/hello_sunflowers.cpp )

target_link_libraries( hello_sunflowers ${OpenCV_LIBS} )
