# The name of our project is "EUSDAB". CMakeLists files in this project can
# refer to the root source directory of the project as ${EUSDAB_SOURCE_DIR} and
# to the root binary directory of the project as ${EUSDAB_BINARY_DIR}.
# minimum version of CMake needed (used version).
cmake_minimum_required(VERSION 2.6)

# Our project name: EUSDAB
project(EUSDAB)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Building in '${CMAKE_BUILD_TYPE}' mode")

# Compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++0x -W -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -Wunused-parameter")

# Debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif()

# EUSDAB include directory
include_directories("include")

# EUSDAB sources
file(GLOB_RECURSE EUSDAB_SOURCES ${EUSDAB_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM EUSDAB_SOURCES ${EUSDAB_SOURCE_DIR}/src/main.cpp)
set(EUSDAB_LIB "EUSDAB_lib")
add_library(${EUSDAB_LIB} ${EUSDAB_SOURCES})

# Boost
set(Boost_MIN_VERSION "1.41.0")
find_package(Boost ${Boost_MIN_VERSION} REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# SFML
set(SFML_ARCH "lib32")
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SFML_ARCH "lib64")
endif()

set(SFML_DIR "${PROJECT_SOURCE_DIR}/lib/SFML-2.0")
set(SFML_LIBS sfml-graphics sfml-audio sfml-window sfml-system)
include_directories("${SFML_DIR}/include")
link_directories("${SFML_DIR}/${SFML_ARCH}")

# Tests
add_subdirectory("tests")
