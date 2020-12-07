#include "mapped_file.h"

#include <string>

#include "util/file.h"

namespace arocketmq {

MappedFile::MappedFile(const fs::path& path, size_t size) : path_(path), size_(size), wrote_position_(0) {
  std::error_code error;
  EnsureRegularFile(path, size, error);
  if (error) {
    // TODO: error
    throw fs::filesystem_error(error.message(), path, error);
  }

  from_offset_ = std::stoll(path.filename());

  mmap_block_ = mmap::make_mmap_sink(path.string(), 0, size, error);
  if (error) {
    // TODO: error
    throw fs::filesystem_error(error.message(), path, error);
  }
}

void MappedFile::AppendData(AppendDataDelegate delegate) {
  size_t current_pos = wrote_position_.load(std::memory_order_acquire);
  if (current_pos < size_) {
    xlib::byte_buffer byte_buffer{mmap_block_.data(), mmap_block_.size()};
    byte_buffer.position(current_pos);
    delegate(from_offset_, std::ref(byte_buffer), size_ - current_pos);
  }
}

}  // namespace arocketmq
