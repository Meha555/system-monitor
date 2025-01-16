#
# Sources
#
aux_source_directory(. SOURCES)

# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

#
# Target
#
add_library(grpc_client SHARED ${SOURCES})
target_include_directories(grpc_client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(grpc_client PUBLIC
    monitor_proto
    glog::glog
)

# INSTALL(TARGETS grpc_client
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )
