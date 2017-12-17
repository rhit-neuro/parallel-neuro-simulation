cmake_minimum_required(VERSION 2.8)

#######################
# Main
#######################

set(SOURCE
    main/main.cpp
)

add_executable(main ${SOURCE})

target_link_libraries(main ${Boost_LIBRARIES} ${Protobuf_LIBRARIES})

#######################
# Main Tests
#######################

set(TEST_SOURCE
    test/main_test.cpp
)

add_executable(main_test ${TEST_SOURCE})

target_link_libraries(main_test ${Boost_LIBRARIES} ${Protobuf_LIBRARIES} gmock gmock_main gtest gtest_main)

add_test(main_test main_test)
