#ifndef AROCKETMQ_UTIL_STRING_H_
#define AROCKETMQ_UTIL_STRING_H_

#include <absl/strings/match.h>
#include <absl/strings/str_join.h>
#include <absl/strings/string_view.h>
#include <xlib/strings/xstring.hpp>

namespace arocketmq {

const xlib::xstring kStrEmpty = "";
const xlib::xstring kStrTrue = "true";
const xlib::xstring kStrFalse = "false";

bool EqualsIgnoreCase(xlib::xstring piece1, absl::string_view piece2);

bool ToBool(xlib::xstring str);

xlib::xstring ToXstring(bool value);

std::string ToHexString(const char* bytes, size_t len);

absl::string_view ToStringView(xlib::xstring str);

}  // namespace arocketmq

#include "detail/str_join.h"

#endif  // AROCKETMQ_UTIL_STRING_H_
