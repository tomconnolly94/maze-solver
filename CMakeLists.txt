cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)

include(CMakePrintHelpers)

# macro to list sub directories of a given directory
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children ${curdir}/*) # This was changed
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${child}) # This was changed
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    LIST(APPEND ${result} ${dirlist})
ENDMACRO()

# declare project
project( MazeSolver )

include(CMakePrintHelpers)

# include opencv
set("OpenCV_DIR" "/usr/lib/x86_64-linux-gnu/cmake/opencv4")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# include header file directories
SUBDIRLIST(SUBDIRS src)

# go one level deeper in each SUBDIR to find nested directories
FOREACH(SUBDIR ${SUBDIRS})
    FILE(GLOB SUBDIRCHILDREN ${SUBDIR}/*)
    FOREACH(SUBDIRCHILD ${SUBDIRCHILDREN})
        IF(IS_DIRECTORY ${SUBDIRCHILD})
            LIST(APPEND SUBDIRS ${SUBDIRCHILD})
        ENDIF()
    ENDFOREACH()
ENDFOREACH()

cmake_print_variables(${SUBDIRS})

include_directories(src ${SUBDIRS})

# include source files
FILE(GLOB cpp_files src/*.cpp src/*/*.cpp src/*/*/*.cpp) # for source

# compile and link
add_executable( MazeSolver ${cpp_files} )
target_link_libraries( MazeSolver ${OpenCV_LIBS} )


#################
# testing config
#################

if("${UNIT_TEST}" STREQUAL "true")

    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    # find_package(GTest REQUIRED)
    include(GoogleTest)

    FILE(GLOB cpp_test_files test/*.cpp ) # for source

    add_executable(
        MazeSolverTest
        ${cpp_test_files}
        ${cpp_files}
    )

    target_link_libraries( MazeSolverTest ${OpenCV_LIBS} )

    target_compile_definitions(MazeSolverTest PRIVATE UNIT_TEST)

    target_link_libraries(
        MazeSolverTest
        GTest::gtest_main
        # ${OpenCV_LIBS}
    )

    gtest_discover_tests(MazeSolverTest)
    
endif()
