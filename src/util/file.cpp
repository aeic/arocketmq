#include "file.h"

namespace arocketmq {

bool EnsureDirectory(const fs::path& directory_path, std::error_code& error_code) noexcept {
  bool result = fs::exists(directory_path, error_code);
  if (error_code) {
    return false;
  }
  if (result) {
    result = fs::is_directory(directory_path, error_code);
    if (error_code) {
      return false;
    }
    if (!result) {
      error_code.assign(EEXIST, std::generic_category());
    }
    return false;
  } else {
    return fs::create_directories(directory_path, error_code);
  }
}

bool EnsureRegularFile(const fs::path& file_path, std::error_code& error_code) noexcept {
  return EnsureRegularFile(file_path, 0, error_code);
}

bool EnsureRegularFile(const fs::path& file_path, size_t file_size, std::error_code& error_code) noexcept {
  bool result = fs::exists(file_path, error_code);
  if (error_code) {
    return false;
  }
  if (result) {
    result = fs::is_regular_file(file_path, error_code);
    if (error_code) {
      return false;
    }
    if (!result) {
      error_code.assign(EEXIST, std::generic_category());
    }
    return false;
  } else {
    // TODO: create file
    error_code.assign(ENOENT, std::generic_category());
    return false;
  }
}

}  // namespace arocketmq
