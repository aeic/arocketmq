#ifndef AROCKETMQ_STORAGE_COMMITLOG_H_
#define AROCKETMQ_STORAGE_COMMITLOG_H_

#include "broker_message_ext_impl.h"
#include "mapped_file_queue.h"

namespace arocketmq {

class CommitLog {
 public:
  CommitLog(const fs::path& commit_log_path, size_t mapped_file_size);

  bool Load();

  void RecoverNormally(int64_t max_physic_offset_of_consume_queue);
  void RecoverAbnormally(int64_t max_physic_offset_of_consume_queue);

  void PutMessage(BrokerMessageExtImpl* msg);

 private:
  void AppendMessage(BrokerMessageExtImpl* msg, int64_t from_offset, xlib::byte_buffer& byte_buffer, size_t max_blank);

  size_t CalculateMessageLength(int sys_flag, size_t body_length, size_t topic_length, size_t properties_length);

  void PutSocketAddress(xlib::byte_buffer& byte_buffer, const struct sockaddr* sa);

 private:
  MappedFileQueue mapped_file_queue_;

  size_t max_message_length_;
};

}  // namespace arocketmq

#endif  // AROCKETMQ_STORAGE_COMMITLOG_H_
