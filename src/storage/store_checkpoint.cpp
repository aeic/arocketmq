#include "store_checkpoint.h"

#include "util/file.h"

namespace arocketmq {

StoreCheckpoint::StoreCheckpoint(const fs::path& checkpoint_path) {
  std::error_code error;
  bool file_exists = !EnsureRegularFile(checkpoint_path, 4096, error);
  if (error) {
    // TODO: error
    throw fs::filesystem_error(error.message(), checkpoint_path, error);
  }

  mmap_ = mmap::make_mmap_sink(checkpoint_path.string(), 0, 4096, error);
  if (error) {
    // TODO: error
    throw fs::filesystem_error(error.message(), checkpoint_path, error);
  }

  mapped_bytes_buffer_.reset(new xlib::byte_buffer{mmap_.data(), mmap_.size()});

  if (file_exists) {
    // log.info("store checkpoint file exists, {}", checkpoint_path);
    physic_msg_timestamp_ = mapped_bytes_buffer_->get<int64_t>(0);
    logics_msg_timestamp_ = mapped_bytes_buffer_->get<int64_t>(8);
    index_msg_timestamp_ = mapped_bytes_buffer_->get<int64_t>(16);

    // log.info("store checkpoint file physicMsgTimestamp " + this.physicMsgTimestamp + ", " +
    //          UtilAll.timeMillisToHumanString(this.physicMsgTimestamp));
    // log.info("store checkpoint file logicsMsgTimestamp " + this.logicsMsgTimestamp + ", " +
    //          UtilAll.timeMillisToHumanString(this.logicsMsgTimestamp));
    // log.info("store checkpoint file indexMsgTimestamp " + this.indexMsgTimestamp + ", " +
    //          UtilAll.timeMillisToHumanString(this.indexMsgTimestamp));
  } else {
    // log.info("store checkpoint file not exists, " + scpPath);
  }
}

}  // namespace arocketmq
