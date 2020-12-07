#ifndef AROCKETMQ_STORAGE_STORECHECKPOINT_H_
#define AROCKETMQ_STORAGE_STORECHECKPOINT_H_

#include <memory>

#include <xlib/io/byte_buffer.hpp>

#include "vm/filesystem.h"
#include "vm/mmap.h"

namespace arocketmq {

class StoreCheckpoint {
 public:
  StoreCheckpoint(const fs::path& checkpoint_path);

 private:
  mmap::mmap_sink mmap_;
  std::unique_ptr<xlib::byte_buffer> mapped_bytes_buffer_;

  int64_t physic_msg_timestamp_ = 0;
  int64_t logics_msg_timestamp_ = 0;
  int64_t index_msg_timestamp_ = 0;
};

}  // namespace arocketmq

#endif  // AROCKETMQ_STORAGE_STORECHECKPOINT_H_
