cmake_minimum_required(VERSION 3.10.2)
project(monitor LANGUAGES CXX)

# set MODULE_PATH for simpler path and shared module
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 不加${PROJECT_SOURCE_DIR}则会认为是cmake执行上下文的路径拼接上bin，效果就是生成在build/里对应文件夹的bin下
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(PkgConfig)

add_subdirectory(proto)
add_subdirectory(grpc)
add_subdirectory(client)
add_subdirectory(broker/cpp)