add_library(arocketmq-vm STATIC)
target_sources(
  arocketmq-vm
  PUBLIC filesystem.h mmap.h process.h
  PRIVATE filesystem.cpp process.cpp)
target_include_directories(arocketmq-vm PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
target_link_libraries(arocketmq-vm PUBLIC ghc_filesystem mio::mio xlib::xlib)
