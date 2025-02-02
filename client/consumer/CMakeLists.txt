set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/misc;${CMAKE_MODULE_PATH}")

#
# Dependencies
#
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Concurrent
)
file(GLOB_RECURSE SOURCES *.cpp)

# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

#
# Target
#
add_executable(monitor-ui ${SOURCES})
set_target_properties(monitor-ui PROPERTIES AUTOMOC TRUE)

target_include_directories(monitor-ui PUBLIC
    ${PROJECT_SOURCE_DIR}/grpc
    .
)

target_link_libraries(monitor-ui
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    grpc_client
    monitor_proto
)

# include(GNUInstallDirs)
# install(TARGETS monitor-ui
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(monitor-ui)
# endif()

# install(TARGETS monitor-ui RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
# install(FILES ${CMAKE_SOURCE_DIR}/monitor-ui@.service DESTINATION lib/systemd/system/)
# install(FILES ${CMAKE_SOURCE_DIR}/monitor-ui.desktop DESTINATION share/applications/)
