cmake_minimum_required(VERSION 3.0)

project(parallel-neuron-simulation)
include(CTest)
include(ExternalProject)

set(MAIN_NAME "parallel-neuro-sim")
set(TEST_SUFFIX "_test")
#######################
# Project Setup
#######################

# Turn on C++ 11 support
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTABC "123" OFF)
if (TESTABC)
#  include_directories(/riscv/include)
#  link_directories(/riscv/lib)
#  set(BOOST_ROOT /riscv)
  set(CMAKE_PREFIX_PATH /riscv)
endif (TESTABC)

######################
# Project Options
#######################

# Build mode (dev/prod)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(BUILD_FOR_DEV TRUE)
  message("Configuring for dev build")
endif()

# Targeting RISC-V
option(
  RISCV
  "Whether to target the RISC-V architecture"
  FALSE
  )
option(
  USE_RISCV_DOCKER_PRESETS
  "Whether to use hardcoded variables for build RISC-V targets in Docker"
  FALSE
  )
if (USE_RISCV_DOCKER_PRESETS)
  set(CMAKE_C_COMPILER /riscv/bin/riscv64-unknown-linux-gnu-gcc CACHE STRING "C compiler" FORCE)
  set(CMAKE_CXX_COMPILER /riscv/bin/riscv64-unknown-linux-gnu-g++ CACHE STRING "C++ compiler" FORCE)
  set(CMAKE_PREFIX_PATH /riscv)
endif (USE_RISCV_DOCKER_PRESETS)
if (USE_RISCV_DOCKER_PRESETS OR RISCV)
  add_definitions(-DRISCV)
endif (USE_RISCV_DOCKER_PRESETS OR RISCV)

# Whether to use OpenMP
option(
  USE_OPENMP
  "Whether OpenMP should be used in this project"
  FALSE
)
if (USE_OPENMP)
  add_definitions(-DUSE_OPENMP)
endif()

# Include LUT support
option(
  INCLUDE_LUT_SUPPORT
  "Whether to allow custom LUT functionalities to be built"
  FALSE
)
if (INCLUDE_LUT_SUPPORT)
  add_definitions(-DINCLUDE_LUT_SUPPORT)
endif()


if (INCLUDE_LUT_SUPPORT AND USE_OPENMP)
  message( FATAL_ERROR "You cannot use -DINCLUDE_LUT_SUPPORT and -DUSE_OPENMP together")
endif()
#######################
# Project Setup
#######################

project(parallel-neuron-simulation)
include(CTest)
include(ExternalProject)

# Turn on C++ 11 support
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#######################
# Compiler Setup
#######################

# OpenMP Support
if (USE_OPENMP)
  include(FindOpenMP)
endif ()

# Enable all warnings
set(WARNING_FLAGS "-Wall -Wextra")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread ${WARNING_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
# Need whole archive linking to bypass a bug that leads to segmentation fault on Debian Linux
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -static -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")

if (BUILD_FOR_DEV)
  set(BUILD_SHARED_LIBS ON)
else ()
  set(BUILD_SHARED_LIBS OFF)
endif ()

#######################
# Project Dependencies
#######################

# Threads
find_package(Threads REQUIRED)

# Boost
if (BUILD_FOR_DEV)
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_STATIC_RUNTIME OFF)
else ()
  set(Boost_USE_STATIC_LIBS ON)
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
