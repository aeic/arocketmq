#include "default_message_store.h"

#include "util/file.h"

namespace arocketmq {

DefaultMessageStroe::DefaultMessageStroe(const fs::path& store_root_dir, size_t mapped_file_size)
    : store_root_dir_(store_root_dir),
      commit_log_(store_root_dir / "commitlog", mapped_file_size),
      persist_executor_("Persist Thread", 1, false) {}

bool DefaultMessageStroe::Load() {
  bool result = true;

  std::error_code error;
  EnsureDirectory(store_root_dir_, error);
  if (error) {
    result = false;
  }

  result = result && commit_log_.Load();

  if (result) {
    store_checkpoint_.reset(new StoreCheckpoint{store_root_dir_ / "checkpoint"});

    Recover(true);
  }

  return result;
}

void DefaultMessageStroe::Recover(bool last_exit_ok) {
  int64_t max_physic_offset_of_consume_queue = RecoverConsumeQueue();

  if (last_exit_ok) {
    commit_log_.RecoverNormally(max_physic_offset_of_consume_queue);
  } else {
    commit_log_.RecoverAbnormally(max_physic_offset_of_consume_queue);
  }

  RecoverTopicQueueTable();
}

int64_t DefaultMessageStroe::RecoverConsumeQueue() {
  return 0;
}

void DefaultMessageStroe::RecoverTopicQueueTable() {}

PutMessageResult DefaultMessageStroe::PutMessage(BrokerMessageExtImpl* msg) {
  PutMessageResult put_message_result;
  persist_executor_
      .submit(std::bind(&DefaultMessageStroe::PutMessageImpl, this, msg,
                        [&](PutMessageResult&& result) { put_message_result = std::move(result); }))
      .wait();
  return put_message_result;
}

// run in persist_executor_(single thread)
void DefaultMessageStroe::PutMessageImpl(BrokerMessageExtImpl* msg, PutMessageImplCallback callback) {
  PutMessageResult result;
  commit_log_.PutMessage(msg);
  if (callback) {
    callback(std::move(result));
  }
}

}  // namespace arocketmq
