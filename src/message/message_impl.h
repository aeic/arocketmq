#ifndef AROCKETMQ_MESSAGE_MESSAGEIMPL_H_
#define AROCKETMQ_MESSAGE_MESSAGEIMPL_H_

#include <xlib/memory/noncopyable.hpp>

#include "message.h"

namespace arocketmq {

/**
 * MessageImpl - Default Message implement
 */
class MessageImpl : public xlib::noncopyable,  // base
                    virtual public Message     // interface
{
 public:
  MessageImpl();
  MessageImpl(xlib::xstring topic, xlib::xstring body);
  MessageImpl(xlib::xstring topic,
              xlib::xstring tags,
              xlib::xstring keys,
              int32_t flag,
              xlib::xstring body,
              bool wait_store_msg_ok);

  virtual ~MessageImpl();

  // topic
  xlib::xstring topic() const override;
  void set_topic(xlib::xstring topic) override;

  // tags
  xlib::xstring tags() const override;
  void set_tags(xlib::xstring tags) override;

  // keys
  xlib::xstring keys() const override;
  void set_keys(xlib::xstring keys) override;
  void set_keys(const std::vector<xlib::xstring>& keys) override;

  // delay time level
  int delay_time_level() const override;
  void set_delay_time_level(int level) override;

  // wait store message ok
  bool wait_store_msg_ok() const override;
  void set_wait_store_msg_ok(bool wait_store_msg_ok) override;

  // flag
  int32_t flag() const override;
  void set_flag(int32_t flag) override;

  // body
  xlib::xstring body() const override;
  void set_body(xlib::xstring body) override;

  // transaction id
  xlib::xstring transaction_id() const override;
  void set_transaction_id(xlib::xstring transaction_id) override;

  // properties
  const std::map<xlib::xstring, xlib::xstring>& properties() const override;
  void set_properties(const std::map<xlib::xstring, xlib::xstring>& properties) override;
  void set_properties(std::map<xlib::xstring, xlib::xstring>&& properties) override;

  // property
  xlib::xstring GetProperty(xlib::xstring name) const override;
  void SetProperty(xlib::xstring name, xlib::xstring value) override;
  void DeleteProperty(xlib::xstring name) override;

 protected:
  xlib::xstring topic_;
  int32_t flag_;
  std::map<xlib::xstring, xlib::xstring> properties_;
  xlib::xstring body_;
  xlib::xstring transaction_id_;
};

}  // namespace arocketmq

#endif  // AROCKETMQ_MESSAGE_MESSAGEIMPL_H_
