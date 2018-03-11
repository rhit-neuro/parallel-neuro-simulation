find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(PROTOBUF_DEFINITION
    protobuf_config.proto
)

protobuf_generate_cpp(PROTO_SRC PROTO_HEADER ${PROTOBUF_DEFINITION})
add_library(proto ${PROTO_HEADER} ${PROTO_SRC})
