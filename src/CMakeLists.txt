cmake_minimum_required(VERSION 2.8)

#######################
# Protobuf Definitions
#######################

add_subdirectory(proto)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#######################
# Main
#######################

# Local header files are placed in the include directory.
include_directories(../include)
set(INCLUDE_SOURCE
  ../include/json-v3.0.0.hpp
)

set(SOURCE
    main/main.cpp
    global/GlobalDefinitions.h

    factory/Factory.h
    factory/EquationFactory.cpp
    factory/InitialConditionFactory.cpp
    logging/ResultLogger.cpp
    logging/ResultLogger.h
    logging/TimeLogger.cpp
    logging/TimeLogger.h
    math/HodgkinHuxley.cpp
    math/ODE.h
    util/ArgParser.cpp
    util/ArgParser.h
    util/JsonToProtobufConfigConverter.cpp
    util/JsonToProtobufConfigConverter.h
)

add_executable(main ${SOURCE} ${INCLUDE_SOURCE} ${PROTO_HEADER} ${PROTO_SRC})

target_link_libraries(main proto ${Boost_LIBRARIES} ${Protobuf_LIBRARIES})

#######################
# Main Tests
#######################

set(TEST_SOURCE
    test/main_test.cpp
)

add_executable(main_test ${TEST_SOURCE} ${PROTO_HEADER} ${PROTO_SRC})

target_link_libraries(main_test proto ${Boost_LIBRARIES} ${Protobuf_LIBRARIES} gmock gmock_main gtest gtest_main)

add_test(main_test main_test)
