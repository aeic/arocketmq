add_library(arocketmq-util STATIC)
target_sources(
  arocketmq-util
  PUBLIC file.h detail/str_join.h "string.h"
  PRIVATE file.cpp "string.cpp")
target_include_directories(arocketmq-util PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
target_link_libraries(arocketmq-util PUBLIC arocketmq-vm absl::strings
                                            absl::time)
