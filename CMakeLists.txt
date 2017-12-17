cmake_minimum_required(VERSION 2.8)
project(CPlusPlusCmakeTemplate)
include(CTest)
include(ExternalProject)
include(FindBoost)
include(FindProtobuf)

#######################
# Project Setup
#######################

# Turn on C++ 11 support
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#######################
# Compiler Setup
#######################

# All Warnings # -Werror -pedantic
set(WARNING_FLAGS "-Wall -Wextra ")
set(SHARED_FLAGS "${WARNING_FLAGS}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
  "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  message(STATUS "Using Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SHARED_FLAGS} -std=c++14 -stdlib=libc++")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  message(STATUS "Using GCC")
  set(CMAKE_CXX_FLAGS "-std=c++11")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SHARED_FLAGS} -std=c++14 -pthread")
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

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # Windows or just missing the library
  # Boost
  set(BOOST_ROOT "")
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_MULTITHREADED ON)
  # Protobuf
  set(PROTOBUF_SRC_ROOT_FOLDER "")
endif ()

# Boost
find_package(Boost COMPONENTS program_options filesystem system)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR, "Boost not found on this system")
endif ()

# Protobuf
find_package(Protobuf)
if (Protobuf_FOUND)
  include_directories(${Protobuf_INCLUDE_DIRS})
else()
  message(FATAL_ERROR, "Protobuf not found on this system")
endif ()

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

# Local header files are placed in the include directory.
include_directories(include)

# Sample Module
add_subdirectory(src)

