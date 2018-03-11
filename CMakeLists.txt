cmake_minimum_required(VERSION 2.8)

project(parallel-neuron-simulation)
include(CTest)
include(ExternalProject)

#######################
# Project Setup
#######################

# Turn on C++ 11 support
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#######################
# Project Options
#######################

# Build mode (dev/prod)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(BUILD_FOR_DEV TRUE)
endif()

#######################
# Compiler Setup
#######################

# OpenMP Support
find_package(OpenMP)

# Enable all warnings
set(WARNING_FLAGS "-Wall -Wextra")
if (BUILD_FOR_DEV)
  set(SHARED_FLAGS "-g ${WARNING_FLAGS} ${OpenMP_CXX_FLAGS}")
else ()
  set(SHARED_FLAGS "-Ofast -static ${WARNING_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
  "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  message(STATUS "Using Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SHARED_FLAGS} -std=c++11 -stdlib=libc++")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  message(STATUS "Using GCC")
  set(CMAKE_CXX_FLAGS "-std=c++11")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SHARED_FLAGS} -std=c++11 -pthread")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  message(STATUS "Using MSVC")
  add_definitions(/MDd /WX- /Wall /D "_CRT_SECURE_NO_WARNINGS")
  # Enable multi-process compilation
  if (NOT MSVC60 AND NOT MSVC70 AND NOT MSVC71)
    List(APPEND CFLAGS /MP)
  endif ()
endif ()

#######################
# Project Dependencies
#######################

# Boost
if (BUILD_FOR_DEV)
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_STATIC_RUNTIME OFF)
else ()
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_STATIC_RUNTIME ON)
endif ()

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

# Protobuf
if (BUILD_FOR_DEV)
  set(Protobuf_USE_STATIC_LIBS OFF)
else()
  set(Protobuf_USE_STATIC_LIBS ON)
endif()

find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})

#######################
# Test Dependencies
#######################

# Testing
enable_testing()

# GTest + GMock
add_subdirectory(lib/gmock-1.7.0)
include_directories(lib/gmock-1.7.0/include)
include_directories(lib/gmock-1.7.0/gtest/include)

#######################
# Project Sources
#######################

# Sample Module
add_subdirectory(src)
