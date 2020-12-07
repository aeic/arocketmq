#ifndef AROCKETMQ_MESSAGE_MESSAGEEXTIMPL_H_
#define AROCKETMQ_MESSAGE_MESSAGEEXTIMPL_H_

#include "message_ext.h"
#include "message_impl.h"

namespace arocketmq {

/**
 * MessageExtImpl -  MessageExt implement
 */
class MessageExtImpl : public MessageImpl,        // base
                       virtual public MessageExt  // interface
{
 public:
  MessageExtImpl();
  MessageExtImpl(int queue_id,
                 int64_t born_timestamp,
                 const struct sockaddr* born_host,
                 int64_t store_timestamp,
                 const struct sockaddr* store_host,
                 xlib::xstring msg_id);

  virtual ~MessageExtImpl();

 public:  // MessageExt
  int32_t store_size() const override;
  void set_store_size(int32_t store_size) override;

  int32_t body_crc() const override;
  void set_body_crc(int32_t body_crc) override;

  int32_t queue_id() const override;
  void set_queue_id(int32_t queue_id) override;

  int64_t queue_offset() const override;
  void set_queue_offset(int64_t queue_offset) override;

  int64_t commit_log_offset() const override;
  void set_commit_log_offset(int64_t physic_offset) override;

  int32_t sys_flag() const override;
  void set_sys_flag(int32_t sys_flag) override;

  int64_t born_timestamp() const override;
  void set_born_timestamp(int64_t born_timestamp) override;

  const struct sockaddr* born_host() const override;
  void set_born_host(const struct sockaddr* born_host) override;

  int64_t store_timestamp() const override;
  void set_store_timestamp(int64_t store_timestamp) override;

  const struct sockaddr* store_host() const override;
  void set_store_host(const struct sockaddr* store_host) override;

  int32_t reconsume_times() const override;
  void set_reconsume_times(int32_t reconsumeTimes) override;

  int64_t prepared_transaction_offset() const override;
  void set_prepared_transaction_offset(int64_t prepared_transaction_offset) override;

  xlib::xstring msg_id() const override;
  void set_msg_id(xlib::xstring msg_id) override;

 private:
  int32_t store_size_;
  int32_t body_crc_;
  int32_t queue_id_;
  int64_t queue_offset_;
  int64_t commit_log_offset_;
  int32_t sys_flag_;
  int64_t born_timestamp_;
  struct sockaddr* born_host_;
  int64_t store_timestamp_;
  struct sockaddr* store_host_;
  int32_t reconsume_times_;
  int64_t prepared_transaction_offset_;
  xlib::xstring msg_id_;
};

class ClientMessageExtImpl : public MessageExtImpl {
 public:  // MessageExt
  xlib::xstring msg_id() const override;
  void set_msg_id(xlib::xstring msg_id) override;

 public:
  xlib::xstring offset_msg_id() const;
  void set_offset_msg_id(xlib::xstring offset_msg_id);
};

}  // namespace arocketmq

#endif  // AROCKETMQ_MESSAGE_MESSAGEEXTIMPL_H_
