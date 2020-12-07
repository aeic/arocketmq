#ifndef AROCKETMQ_STORAGE_MAPPEDFILEQUEUE_H_
#define AROCKETMQ_STORAGE_MAPPEDFILEQUEUE_H_

#include <memory>
#include <string>
#include <vector>

#include "mapped_file.h"
#include "vm/filesystem.h"

namespace arocketmq {

class MappedFileQueue {
 public:
  MappedFileQueue(const fs::path& mapped_file_dir, size_t mapped_file_size);

  bool Load();

  MappedFile* GetLastMappedFile();
  MappedFile* GetLastMappedFile(int64_t start_offset, bool need_create = true);

 private:
  std::string OffsetToFilename(int64_t offset);

 public:
  inline std::vector<std::unique_ptr<MappedFile>>& mapped_files() { return mapped_files_; }

 private:
  fs::path mapped_file_dir_;
  size_t mapped_file_size_;

  std::vector<std::unique_ptr<MappedFile>> mapped_files_;
};

}  // namespace arocketmq

#endif  // AROCKETMQ_STORAGE_MAPPEDFILEQUEUE_H_
