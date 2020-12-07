#ifndef AROCKETMQ_STORAGE_BROKERMESSAGEEXTIMPL_H_
#define AROCKETMQ_STORAGE_BROKERMESSAGEEXTIMPL_H_

#include "message/message_ext_impl.h"

namespace arocketmq {

class BrokerMessageExtImpl : public MessageExtImpl {
 public:
  BrokerMessageExtImpl();

  inline xlib::xstring properties_string() const { return properties_string_; }
  inline void set_properties_string(xlib::xstring properties_string) { properties_string_ = properties_string; }

 private:
  xlib::xstring properties_string_;
};

}  // namespace arocketmq

#endif  // AROCKETMQ_STORAGE_BROKERMESSAGEEXTIMPL_H_
