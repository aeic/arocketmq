#ifndef AROCKETMQ_MESSAGE_MESSAGE_H_
#define AROCKETMQ_MESSAGE_MESSAGE_H_

#include <cstdint>

#include <map>
#include <vector>

#include <xlib/strings/xstring.hpp>

namespace arocketmq {

/**
 * Message - interface for messgae
 */
class Message {
 public:
  virtual ~Message() = default;

 public:
  // topic
  virtual xlib::xstring topic() const = 0;
  virtual void set_topic(xlib::xstring topic) = 0;

  // tags
  virtual xlib::xstring tags() const = 0;
  virtual void set_tags(xlib::xstring tags) = 0;

  // keys
  virtual xlib::xstring keys() const = 0;
  virtual void set_keys(xlib::xstring keys) = 0;
  virtual void set_keys(const std::vector<xlib::xstring>& keys) = 0;

  // delay time level
  virtual int delay_time_level() const = 0;
  virtual void set_delay_time_level(int level) = 0;

  // wait store message ok
  virtual bool wait_store_msg_ok() const = 0;
  virtual void set_wait_store_msg_ok(bool wait_store_msg_ok) = 0;

  // flag
  virtual int32_t flag() const = 0;
  virtual void set_flag(int32_t flag) = 0;

  // body
  virtual xlib::xstring body() const = 0;
  virtual void set_body(xlib::xstring body) = 0;

  // transaction id
  virtual xlib::xstring transaction_id() const = 0;
  virtual void set_transaction_id(xlib::xstring transaction_id) = 0;

  // properties
  virtual const std::map<xlib::xstring, xlib::xstring>& properties() const = 0;
  virtual void set_properties(const std::map<xlib::xstring, xlib::xstring>& properties) = 0;
  virtual void set_properties(std::map<xlib::xstring, xlib::xstring>&& properties) = 0;

 public:
  // property
  virtual xlib::xstring GetProperty(xlib::xstring name) const = 0;
  virtual void SetProperty(xlib::xstring name, xlib::xstring value) = 0;
  virtual void DeleteProperty(xlib::xstring name) = 0;

  // batch flag
  virtual bool Batch() const { return false; }
};

}  // namespace arocketmq

#endif  // AROCKETMQ_MESSAGE_MESSAGE_H_
