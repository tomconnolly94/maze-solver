cmake_minimum_required(VERSION 3.8)

# macro to list sub directories of a given directory
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children ${curdir}/*) # This was changed
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${child}) # This was changed
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

# declare project
project( MazeSolver )

# include print function, example use: `cmake_print_variables(<var-to-print>)`
include(CMakePrintHelpers)

# include opencv
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# include header file directories
SUBDIRLIST(SUBDIRS src)
include_directories(src ${SUBDIRS})

# include source files
FILE(GLOB cpp_files src/*.cpp src/*/*.cpp) # for source

# compile and link
add_executable( MazeSolver ${cpp_files} )
target_link_libraries( MazeSolver ${OpenCV_LIBS} )
