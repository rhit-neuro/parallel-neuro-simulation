cmake_minimum_required(VERSION 2.8)

#######################
# Protobuf Definitions
#######################

add_subdirectory(proto)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#######################
# Main
#######################

set(SOURCE
    main/main.cpp
)

add_executable(main ${SOURCE} ${PROTO_HEADER} ${PROTO_SRC})

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
