cmake_minimum_required(VERSION 3.0)

#######################
# Protobuf Definitions
#######################

add_subdirectory(proto)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#######################
# Main
#######################

# Local header files are placed in the include directory.
include_directories(include)
set(
  INCLUDE_SOURCE

  include/json-3.1.2/json.hpp
  include/lut_support-a7d4c9fa7d6a4c1a5c1494d29d99617b392c8255/lut_support.h
)

set(
  SOURCE

  main/main.cpp
  main/global/GlobalDefinitions.h

  main/config/ProgramConfig.cpp
  main/config/ProgramConfig.h
  main/config/ProgramConfigTrivialMethods.cpp
  main/factory/Factory.h
  main/factory/EquationFactory.cpp
  main/logging/AsyncBuffer.cpp
  main/logging/AsyncBuffer.h
  main/logging/ResultLogger.cpp
  main/logging/ResultLogger.h
  main/logging/TimeLogger.cpp
  main/logging/TimeLogger.h
  main/math/HardLUT.cpp
  main/math/HodgkinHuxley.cpp
  main/math/HodgkinHuxleyCurrent.cpp
  main/math/HodgkinHuxleyCurve.cpp
  main/math/HodgkinHuxleyLUT.cpp
  main/math/HodgkinHuxleyLUTCurve.cpp
  main/math/LUT.h
  main/math/ODE.h
  main/math/SoftLUT.cpp
  main/util/ArgParser.cpp
  main/util/ArgParser.h
  main/util/JsonToProtobufConfigConverter.cpp
  main/util/JsonToProtobufConfigConverter.h
)

add_executable(${MAIN_NAME} ${SOURCE} ${INCLUDE_SOURCE} ${PROTO_HEADER} ${PROTO_SRC})

target_link_libraries(${MAIN_NAME} proto ${Boost_LIBRARIES} ${Protobuf_LIBRARIES})

#######################
# Main Tests
#######################

set(TEST_SOURCE
  test/main_test.cpp
)

add_executable(${MAIN_NAME}${TEST_SUFFIX} ${TEST_SOURCE} ${PROTO_HEADER} ${PROTO_SRC})

target_link_libraries(${MAIN_NAME}${TEST_SUFFIX} proto ${Boost_LIBRARIES} ${Protobuf_LIBRARIES} gmock gmock_main gtest gtest_main)

add_test(${MAIN_NAME}${TEST_SUFFIX} ${MAIN_NAME}${TEST_SUFFIX})

install(TARGETS ${MAIN_NAME} DESTINATION bin)
