#ifndef AROCKETMQ_STORAGE_MAPPEDFILE_H_
#define AROCKETMQ_STORAGE_MAPPEDFILE_H_

#include <cstddef>
#include <cstdint>

#include <atomic>
#include <functional>
#include <memory>

#include <xlib/io/byte_buffer.hpp>

#include "vm/filesystem.h"
#include "vm/mmap.h"

namespace arocketmq {

class MappedFile {
 public:
  typedef std::function<void(int64_t from_offset, xlib::byte_buffer& byte_buffer, size_t max_blank)> AppendDataDelegate;

 public:
  MappedFile(const fs::path& file_path, size_t file_size);

  void AppendData(AppendDataDelegate delegate);

  bool Full() { return false; }

 public:
  inline int64_t from_offset() { return from_offset_; }
  inline mmap::mmap_sink& mmap_block() { return mmap_block_; }

 private:
  fs::path path_;
  size_t size_;
  int64_t from_offset_;

  mmap::mmap_sink mmap_block_;

  std::atomic<size_t> wrote_position_;
};

}  // namespace arocketmq

#endif  // AROCKETMQ_STORAGE_MAPPEDFILE_H_
