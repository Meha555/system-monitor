aux_source_directory(. SOURCES)

add_executable(monitor-server ${SOURCES})
target_include_directories(monitor-server PUBLIC
    ${PROJECT_SOURCE_DIR}/3rd-party
)
target_link_libraries(monitor-server PUBLIC
    monitor_proto
    grpc_server
)