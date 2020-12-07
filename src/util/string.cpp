#include "string.h"

namespace arocketmq {

bool EqualsIgnoreCase(xlib::xstring piece1, absl::string_view piece2) {
  absl::string_view sv(piece1.data(), piece1.length());
  return absl::EqualsIgnoreCase(sv, piece2);
}

bool ToBool(xlib::xstring str) {
  return EqualsIgnoreCase(str, "true");
}

xlib::xstring ToXstring(bool value) {
  return value ? kStrTrue : kStrFalse;
}

static const char kHexAlphabet[] = "0123456789ABCDEF";

std::string ToHexString(const char* bytes, size_t len) {
  if (bytes == nullptr || len <= 0) {
    return "";
  }

  std::string buffer;
  buffer.reserve(len * 2 + 1);
  for (std::size_t i = 0; i < len; i++) {
    uint8_t v = (uint8_t)bytes[i];
    buffer.append(1, kHexAlphabet[v >> 4]);
    buffer.append(1, kHexAlphabet[v & 0x0FU]);
  }
  return buffer;
}

absl::string_view ToStringView(xlib::xstring str) {
  return absl::string_view(str.data(), str.length());
}

}  // namespace arocketmq
