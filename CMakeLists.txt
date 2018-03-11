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
  message("Configuring for dev build")
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
  set(BUILD_SHARED_LIBS ON)
else ()
  set(SHARED_FLAGS "-Ofast -static ${WARNING_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(BUILD_SHARED_LIBS OFF)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SHARED_FLAGS} -std=c++11 -pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

#######################
# Project Dependencies
#######################

# Boost
if (BUILD_FOR_DEV)
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_STATIC_RUNTIME OFF)
else ()
  # TODO Temporarily disable because even with Protobuf_USE_STATIC_LIBS, Protobuf is linked dynamically
  # If we force Boost to be linked statically, Protobuf will be explicitly labeled as dynamic
  # Right neither are labeled explicitly, which actually saves us the hassle
  #set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_STATIC_RUNTIME ON)
endif ()

find_package(Boost COMPONENTS program_options filesystem system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

# Protobuf
if (BUILD_FOR_DEV)
  set(Protobuf_USE_STATIC_LIBS OFF)
else()
  set(Protobuf_USE_STATIC_LIBS ON)
endif()

find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

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
