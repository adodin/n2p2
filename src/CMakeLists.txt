###################################################################################################
# CMake Build System for n2p2
###################################################################################################

###################################################################################################
# Project & CMake Information
cmake_minimum_required(VERSION 3.16)    # Same required version as LAMMPS (no extra dependencies)
project(n2p2)
###################################################################################################

###################################################################################################
# Set C++ Standard
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
endif()
if(CMAKE_CXX_STANDARD LESS 11)
    message(FATAL_ERROR "C++ standard must be set to at least 11")
endif()
###################################################################################################

###################################################################################################
# Project Path Variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(PROJECT_INCLUDE ${CMAKE_BINARY_DIR}/../include)
set(CMAKE_SHARED_LIBRARY_SUFFIX .so)
###################################################################################################

###################################################################################################
# Document CLI Option Defaults
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
###################################################################################################

###################################################################################################
# Go into each subdirectory
add_subdirectory(libnnp)
add_subdirectory(libnnptrain)
###################################################################################################