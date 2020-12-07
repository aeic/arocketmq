#ifndef AROCKETMQ_UTIL_DETAIL_STRJOIN_H_
#define AROCKETMQ_UTIL_DETAIL_STRJOIN_H_

#include <absl/strings/internal/str_join_internal.h>
#include <xlib/strings/xstring.hpp>

#include "util/string.h"

namespace arocketmq {

namespace detail {

struct XstringFormatter {
  // This template is needed in order to support passing in a dereferenced
  // vector<bool>::iterator
  template <typename T>
  void operator()(std::string* out, const T& t) const {
    StrAppend(out, absl::AlphaNum(t));
  }

  void operator()(std::string* out, const absl::AlphaNum& t) const { absl::StrAppend(out, t); }

  void operator()(std::string* out, const xlib::xstring& t) const {
    absl::StrAppend(out, absl::AlphaNum(arocketmq::ToStringView(t)));
  }
};

}  // namespace detail

}  // namespace arocketmq

template <>
struct absl::strings_internal::DefaultFormatter<xlib::xstring> {
  typedef arocketmq::detail::XstringFormatter Type;
};

#endif  // AROCKETMQ_UTIL_DETAIL_STRJOIN_H_
