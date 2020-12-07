#ifndef AROCKETMQ_STORAGE_DEFAULTMESSAGESTORE_H_
#define AROCKETMQ_STORAGE_DEFAULTMESSAGESTORE_H_

#include <functional>
#include <future>
#include <memory>

#include <xlib/executor/executor.hpp>

#include "commit_log.h"
#include "put_message_result.h"
#include "store_checkpoint.h"

namespace arocketmq {

class DefaultMessageStroe {
 public:
  typedef std::function<void(PutMessageResult&&)> PutMessageImplCallback;

 public:
  DefaultMessageStroe(const fs::path& store_path, size_t mapped_file_size);

  bool Load();

  PutMessageResult PutMessage(BrokerMessageExtImpl* msg);

 private:
  void Recover(bool last_exit_ok);
  int64_t RecoverConsumeQueue();
  void RecoverTopicQueueTable();

  void PutMessageImpl(BrokerMessageExtImpl* msg, PutMessageImplCallback callback);

 private:
  fs::path store_root_dir_;

  CommitLog commit_log_;
  std::unique_ptr<StoreCheckpoint> store_checkpoint_;

  xlib::thread_pool_executor persist_executor_;
};

}  // namespace arocketmq

#endif  // AROCKETMQ_STORAGE_DEFAULTMESSAGESTORE_H_
