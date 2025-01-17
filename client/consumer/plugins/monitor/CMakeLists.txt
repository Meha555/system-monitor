message(STATUS "Building Plugins")

set(LIBRARY_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH}/monitor)
set(INC_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(cpu-monitor)
add_subdirectory(memory-monitor)
add_subdirectory(network-monitor)
add_subdirectory(softirq-monitor)