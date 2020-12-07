#ifndef AROCKETMQ_MESSAGE_MESSAGEACCESSOR_HPP_
#define AROCKETMQ_MESSAGE_MESSAGEACCESSOR_HPP_

#include <algorithm>

#include "message.h"
#include "message_const.h"

namespace arocketmq {

namespace MessageAccessor {

inline void DeleteProperty(Message& msg, xlib::xstring name) {
  msg.DeleteProperty(std::move(name));
}

inline void SetProperties(Message& msg, std::map<xlib::xstring, xlib::xstring>&& properties) {
  msg.set_properties(std::move(properties));
}

inline void SetProperty(Message& msg, xlib::xstring name, xlib::xstring value) {
  msg.SetProperty(name, value);
}

inline xlib::xstring GetReconsumeTime(Message& msg) {
  return msg.GetProperty(MessageConst::PROPERTY_RECONSUME_TIME);
}

inline xlib::xstring GetMaxReconsumeTimes(Message& msg) {
  return msg.GetProperty(MessageConst::PROPERTY_MAX_RECONSUME_TIMES);
}

inline void SetConsumeStartTimeStamp(Message& msg, xlib::xstring consume_start_timestamp) {
  SetProperty(msg, MessageConst::PROPERTY_CONSUME_START_TIMESTAMP, std::move(consume_start_timestamp));
}

}  // namespace MessageAccessor

}  // namespace arocketmq

#endif  // AROCKETMQ_MESSAGE_MESSAGEACCESSOR_HPP_
