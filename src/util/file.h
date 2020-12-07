#ifndef AROCKETMQ_UTIL_FILE_H_
#define AROCKETMQ_UTIL_FILE_H_

#include <system_error>

#include "vm/filesystem.h"

namespace arocketmq {

bool EnsureDirectory(const fs::path& directory_path, std::error_code& error_code) noexcept;

bool EnsureRegularFile(const fs::path& file_path, std::error_code& error_code) noexcept;
bool EnsureRegularFile(const fs::path& file_path, size_t file_size, std::error_code& error_code) noexcept;

}  // namespace arocketmq

#endif  // AROCKETMQ_UTIL_FILE_H_
