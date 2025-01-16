find_package(glog REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/3rd-party)

add_subdirectory(server)
add_subdirectory(client)