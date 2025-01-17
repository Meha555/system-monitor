find_package(glog REQUIRED)
find_package(gflags REQUIRED)

file(GLOB_RECURSE SOURCES *.cpp)

add_executable(monitord ${SOURCES})

target_include_directories(monitord PUBLIC
  monitor
  monitor/factory
  utils
  ${PROJECT_SOURCE_DIR}/grpc
  ${PROJECT_SOURCE_DIR}/3rd-party
)

target_link_libraries(monitord
    PUBLIC
    monitor_proto
    grpc_client
    glog::glog
    gflags
)