add_library(arocketmq-storage STATIC)
target_sources(
  arocketmq-storage
  PUBLIC broker_message_ext_impl.h
         mapped_file.h
         mapped_file_queue.h
         commit_log.h
         store_checkpoint.h
         put_message_result.h
         default_message_store.h
  PRIVATE broker_message_ext_impl.cpp mapped_file.cpp mapped_file_queue.cpp
          commit_log.cpp store_checkpoint.cpp default_message_store.cpp)
target_include_directories(arocketmq-storage
                           PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
target_link_libraries(arocketmq-storage PUBLIC arocketmq-util arocketmq-vm
                                               absl::str_format xlib::xlib)
