#include "mapped_file_queue.h"

#include <algorithm>
#include <vector>

#include <absl/strings/str_format.h>

#include "util/file.h"

namespace arocketmq {

MappedFileQueue::MappedFileQueue(const fs::path& mapped_file_dir, size_t mapped_file_size)
    : mapped_file_dir_(mapped_file_dir), mapped_file_size_(mapped_file_size) {}

bool MappedFileQueue::Load() {
  std::error_code error;
  EnsureDirectory(mapped_file_dir_, error);
  if (error) {
    // TODO: error
    return false;
  }

  std::vector<fs::path> files;
  for (auto& entry : fs::directory_iterator{mapped_file_dir_}) {
    if (!entry.is_regular_file()) {
      return false;
    }
    if (entry.file_size() != mapped_file_size_) {
      //       log.warn(file + "\t" + file.length() +
      //                " length not matched message store config value, please check it manually");
      return false;
    }
    files.push_back(entry.path());
  }

  std::sort(files.begin(), files.end());
  for (auto& file_path : files) {
    try {
      auto* mapped_file = new MappedFile{file_path, mapped_file_size_};
      //       mappedFile.setWrotePosition(this.mappedFileSize);
      //       mappedFile.setFlushedPosition(this.mappedFileSize);
      //       mappedFile.setCommittedPosition(this.mappedFileSize);
      mapped_files_.emplace_back(mapped_file);
      //       log.info("load " + file.getPath() + " OK");
    } catch (const std::exception& e) {
      //       log.error("load file " + file + " error", e);
      return false;
    }
  }

  return true;
}

MappedFile* MappedFileQueue::GetLastMappedFile() {
  MappedFile* last_mapped_file = nullptr;

  if (mapped_files_.size() > 0) {
    last_mapped_file = mapped_files_.back().get();
  }

  return last_mapped_file;
}

MappedFile* MappedFileQueue::GetLastMappedFile(int64_t start_offset, bool need_create) {
  int64_t create_offset = 0;
  auto* last_mapped_file = GetLastMappedFile();

  if (nullptr == last_mapped_file) {
    create_offset = start_offset - (start_offset % mapped_file_size_);
  } else if (last_mapped_file->Full()) {
    create_offset = last_mapped_file->from_offset() + mapped_file_size_;
  }

  if (nullptr == last_mapped_file && need_create) {
    auto next_file_path = mapped_file_dir_ / OffsetToFilename(create_offset);
    MappedFile* mapped_file = nullptr;

    try {
      mapped_file = new MappedFile{next_file_path, mapped_file_size_};
    } catch (const std::exception& e) {
      // log.error("create mappedFile exception", e);
    }

    if (mapped_file != nullptr) {
      if (mapped_files_.empty()) {
        // mapped_file.setFirstCreateInQueue(true);
      }
      mapped_files_.emplace_back(mapped_file);
    }

    return mapped_file;
  }

  return last_mapped_file;
}

std::string MappedFileQueue::OffsetToFilename(int64_t offset) {
  return absl::StrFormat("%020i", offset);
}

}  // namespace arocketmq
