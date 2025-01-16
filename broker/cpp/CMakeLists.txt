aux_source_directory(. SOURCES)

add_executable(monitor-broker ${SOURCES})
target_include_directories(monitor-broker PUBLIC
    ${PROJECT_SOURCE_DIR}/3rd-party
)
target_link_libraries(monitor-broker PUBLIC
    monitor_proto
    grpc_server
)