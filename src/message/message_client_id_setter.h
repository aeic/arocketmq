#ifndef AROCKETMQ_MESSAGE_CLIENT_ID_SETTER_H_
#define AROCKETMQ_MESSAGE_CLIENT_ID_SETTER_H_

#include "message.h"
#include "message_accessor.h"
#include "message_const.h"

namespace arocketmq {

namespace MessageClientIDSetter {

xlib::xstring CreateUniqID();

inline xlib::xstring GetUniqID(const Message& msg) {
  return msg.GetProperty(MessageConst::PROPERTY_UNIQ_CLIENT_MESSAGE_ID_KEYIDX);
}

inline void SetUniqID(Message& msg) {
  if (msg.GetProperty(MessageConst::PROPERTY_UNIQ_CLIENT_MESSAGE_ID_KEYIDX).empty()) {
    MessageAccessor::SetProperty(msg, MessageConst::PROPERTY_UNIQ_CLIENT_MESSAGE_ID_KEYIDX, CreateUniqID());
  }
}

}  // namespace MessageClientIDSetter

}  // namespace arocketmq

#endif  // AROCKETMQ_MESSAGE_CLIENT_ID_SETTER_H_
