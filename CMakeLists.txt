cmake_minimum_required(VERSION 2.8)
project( MazeSolver )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( MazeSolver src/main.cpp src/ImageLoader.cpp )
# target_include_directories(MazeSolver
#  PRIVATE
#   src)
include_directories(src)
target_link_libraries( MazeSolver ${OpenCV_LIBS} )