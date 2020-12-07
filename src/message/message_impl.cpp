#include "message_impl.h"

#include <algorithm>  // std::move

#include "message_const.h"
#include "util/string.h"

namespace arocketmq {

MessageImpl::MessageImpl() : MessageImpl(kStrEmpty, kStrEmpty) {}

MessageImpl::MessageImpl(xlib::xstring topic, xlib::xstring body)
    : MessageImpl(std::move(topic), kStrEmpty, kStrEmpty, 0, std::move(body), true) {}

MessageImpl::MessageImpl(xlib::xstring topic,
                         xlib::xstring tags,
                         xlib::xstring keys,
                         int32_t flag,
                         xlib::xstring body,
                         bool wait_store_msg_ok)
    : topic_(std::move(topic)), flag_(flag), body_(std::move(body)), transaction_id_(kStrEmpty) {
  if (tags.length() > 0) {
    set_tags(std::move(tags));
  }

  if (keys.length() > 0) {
    set_keys(std::move(keys));
  }

  set_wait_store_msg_ok(wait_store_msg_ok);
}

MessageImpl::~MessageImpl() = default;

xlib::xstring MessageImpl::topic() const {
  return topic_;
}

void MessageImpl::set_topic(xlib::xstring topic) {
  topic_ = topic;
}

xlib::xstring MessageImpl::tags() const {
  return GetProperty(MessageConst::PROPERTY_TAGS);
}

void MessageImpl::set_tags(xlib::xstring tags) {
  SetProperty(MessageConst::PROPERTY_TAGS, tags);
}

xlib::xstring MessageImpl::keys() const {
  return GetProperty(MessageConst::PROPERTY_KEYS);
}

void MessageImpl::set_keys(xlib::xstring keys) {
  SetProperty(MessageConst::PROPERTY_KEYS, keys);
}

void MessageImpl::set_keys(const std::vector<xlib::xstring>& keys) {
  if (keys.empty()) {
    return;
  } else if (keys.size() == 1) {
    set_keys(keys[0]);
  } else {
    set_keys(absl::StrJoin(keys, ToStringView(MessageConst::KEY_SEPARATOR)));
  }
}

int MessageImpl::delay_time_level() const {
  xlib::xstring tmp = GetProperty(MessageConst::PROPERTY_DELAY_TIME_LEVEL);
  if (!tmp.empty()) {
    return stoi(tmp.str());
  }
  return 0;
}

void MessageImpl::set_delay_time_level(int level) {
  SetProperty(MessageConst::PROPERTY_DELAY_TIME_LEVEL, std::to_string(level));
}

bool MessageImpl::wait_store_msg_ok() const {
  xlib::xstring tmp = GetProperty(MessageConst::PROPERTY_WAIT_STORE_MSG_OK);
  return tmp.empty() || ToBool(tmp);
}

void MessageImpl::set_wait_store_msg_ok(bool wait_store_msg_ok) {
  SetProperty(MessageConst::PROPERTY_WAIT_STORE_MSG_OK, ToXstring(wait_store_msg_ok));
}

int32_t MessageImpl::flag() const {
  return flag_;
}

void MessageImpl::set_flag(int32_t flag) {
  flag_ = flag;
}

xlib::xstring MessageImpl::body() const {
  return body_;
}

void MessageImpl::set_body(xlib::xstring body) {
  body_ = body;
}

xlib::xstring MessageImpl::transaction_id() const {
  return transaction_id_;
}

void MessageImpl::set_transaction_id(xlib::xstring transactionId) {
  transaction_id_ = transactionId;
}

const std::map<xlib::xstring, xlib::xstring>& MessageImpl::properties() const {
  return properties_;
}

void MessageImpl::set_properties(const std::map<xlib::xstring, xlib::xstring>& properties) {
  properties_ = properties;
}

void MessageImpl::set_properties(std::map<xlib::xstring, xlib::xstring>&& properties) {
  properties_ = std::move(properties);
}

xlib::xstring MessageImpl::GetProperty(xlib::xstring name) const {
  const auto& it = properties_.find(name);
  if (it != properties_.end()) {
    return it->second;
  }
  return kStrEmpty;
}

void MessageImpl::SetProperty(xlib::xstring name, xlib::xstring value) {
  properties_[name] = value;
}

void MessageImpl::DeleteProperty(xlib::xstring name) {
  properties_.erase(name);
}

}  // namespace arocketmq
