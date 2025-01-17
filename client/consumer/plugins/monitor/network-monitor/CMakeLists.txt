set(PLUGIN_NAME "network-monitor")
project(${PLUGIN_NAME})

file(GLOB_RECURSE SRCS *.cpp)

find_package(Qt5Widgets REQUIRED)

add_definitions("${QT_DEFINITIONS} -DQT_PLUGIN")

add_library(${PLUGIN_NAME} SHARED ${SRCS} ${INC_DIRS}/monitor_widget.cpp)
target_include_directories(${PLUGIN_NAME} PUBLIC
    ${INC_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${PLUGIN_NAME} PRIVATE
    Qt5::Widgets
)

# install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION lib/monitor-ui/plugins)