find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

#
# Protobuf/Grpc source files
#
file(GLOB_RECURSE PROTO_FILES *.proto)

#
# Add Library target with protobuf sources
#
add_library(monitor_proto SHARED ${PROTO_FILES})
target_link_libraries(monitor_proto PUBLIC
    protobuf::libprotobuf
    gRPC::grpc
    gRPC::grpc++
)
target_include_directories(monitor_proto PUBLIC
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

#
# Compile protobuf and grpc files in mointor proto target to cpp
#
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET monitor_proto LANGUAGE cpp)
protobuf_generate(TARGET monitor_proto LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")
