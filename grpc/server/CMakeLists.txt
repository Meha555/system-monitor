#
# Sources
#
aux_source_directory(. SOURCES)

# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

#
# Target
#
add_library(grpc_server SHARED ${SOURCES})
target_include_directories(grpc_server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(grpc_server PUBLIC
    monitor_proto
    glog::glog
)
