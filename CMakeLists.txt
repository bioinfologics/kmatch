cmake_minimum_required (VERSION 2.8)

IF (MY_COMPILER_OPTION STREQUAL "Intel")
    FIND_PROGRAM(ICPC_PROGRAM icpc ...)
    IF(ICPC_PROGRAM)
        MESSAGE(STATUS "** Compiling with Intel settings **")
        IF(ENV{CXX})
            MESSAGE(WARNING "Overwriting CXX envvar")
        ENDIF()
        SET(ENV{CXX} "${ICPC_PROGRAM}")
        SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -w")
        SET(CMAKE_CXX_FLAGS_DEBUG "-g")
    ELSE()
        MESSAGE(FATAL_ERROR "Intel compiler not found")
    ENDIF()
ENDIF ()

project (kmatch)

#FIND_PACKAGE( OpenMP REQUIRED)
#if(OPENMP_FOUND)
#    message("OPENMP FOUND")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif()

## Compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -w -Wno-deprecated -std=c++14")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

find_package (Threads)


#SET(CMAKE_CXX_LINK_EXECUTABLE "/usr/bin/ld")
add_definitions(${CMAKE_CXX_FLAGS})

## To move the bins to the final location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

#if (DEFINED ZLIB_PATH)
#  include_directories("${ZLIB_PATH}/include")
#  link_directories("${ZLIB_PATH}/lib")
#else()
#    set(ZLIB_PATH "/usr/lib" CACHE FILEPATH "ZLIB Library path")
#endif()

#find_package(ZLIB REQUIRED)
#if (ZLIB_FOUND)
#    include_directories(${ZLIB_INCLUDE_DIRS})
#endif()

## Include directories
include_directories("src/")

## Mac compilation issue
#include_directories("/usr/include/malloc")

## Set sources variables

## add executables and respective sources
add_executable(kmatch src/KMatch.cc)

add_executable(kmatch-dump src/matchdump.cc)

target_link_libraries (kmatch ${CMAKE_THREAD_LIBS_INIT})