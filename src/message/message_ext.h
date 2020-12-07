#ifndef AROCKETMQ_MESSAGE_MESSAGEEXT_H_
#define AROCKETMQ_MESSAGE_MESSAGEEXT_H_

#ifdef WIN32
// clang-format off
#include <Winsock2.h>
#include <Windows.h>
// clang-format on
#else
#include <sys/socket.h>
#endif

#include "message.h"

namespace arocketmq {

/**
 * MessageExt - Message extend interface, which was generated on broker
 */
class MessageExt : virtual public Message  // base interface
{
 public:
  virtual ~MessageExt() = default;

  virtual int32_t store_size() const = 0;
  virtual void set_store_size(int32_t store_size) = 0;

  virtual int32_t body_crc() const = 0;
  virtual void set_body_crc(int32_t body_crc) = 0;

  virtual int32_t queue_id() const = 0;
  virtual void set_queue_id(int32_t queue_id) = 0;

  virtual int64_t queue_offset() const = 0;
  virtual void set_queue_offset(int64_t queue_offset) = 0;

  virtual int64_t commit_log_offset() const = 0;
  virtual void set_commit_log_offset(int64_t physic_offset) = 0;

  virtual int32_t sys_flag() const = 0;
  virtual void set_sys_flag(int32_t sysFlag) = 0;

  virtual int64_t born_timestamp() const = 0;
  virtual void set_born_timestamp(int64_t born_timestamp) = 0;

  virtual const struct sockaddr* born_host() const = 0;
  virtual void set_born_host(const struct sockaddr* born_host) = 0;

  virtual int64_t store_timestamp() const = 0;
  virtual void set_store_timestamp(int64_t store_timestamp) = 0;

  virtual const struct sockaddr* store_host() const = 0;
  virtual void set_store_host(const struct sockaddr* store_host) = 0;

  virtual int32_t reconsume_times() const = 0;
  virtual void set_reconsume_times(int32_t reconsume_times) = 0;

  virtual int64_t prepared_transaction_offset() const = 0;
  virtual void set_prepared_transaction_offset(int64_t prepared_transaction_offset) = 0;

  virtual xlib::xstring msg_id() const = 0;
  virtual void set_msg_id(xlib::xstring msgId) = 0;
};

}  // namespace arocketmq

#endif  // AROCKETMQ_MESSAGE_MESSAGEEXT_H_
