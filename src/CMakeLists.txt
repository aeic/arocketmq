add_subdirectory(vm)
add_subdirectory(util)

add_library(arocketmq-common STATIC)
target_include_directories(arocketmq-common PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(arocketmq-common PUBLIC arocketmq-util)
add_subdirectory(message)

add_subdirectory(storage)

add_executable(mqbroker)
target_sources(mqbroker PRIVATE main.cpp)
target_link_libraries(mqbroker PRIVATE arocketmq-storage xlib::xlib)
