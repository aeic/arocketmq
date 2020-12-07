#include "network.h"

#include <cstdlib>
#include <cstring>

#include <vector>

#include <absl/strings/str_split.h>

namespace arocketmq {

static std::string sLocalIpAddress;

struct sockaddr* CopySocketAddress(struct sockaddr* dest, const struct sockaddr* src) {
  if (src != nullptr) {
    if (dest == nullptr || dest->sa_family != src->sa_family) {
      dest = (struct sockaddr*)std::realloc(dest, sizeof(union sockaddr_union));
    }
    std::memcpy(dest, src, sockaddr_size(src));
  } else {
    std::free(dest);
    dest = nullptr;
  }
  return dest;
}

std::string GetLocalAddress() {
  if (sLocalIpAddress.empty()) {
    auto hostname = GetLocalHostName();
    if (!hostname.empty()) {
      try {
        sLocalIpAddress = SocketAddress2String(LookupNameServers(hostname));
      } catch (std::exception& e) {
        sLocalIpAddress = "127.0.0.1";
      }
    }
  }
  return sLocalIpAddress;
}

uint32_t GetIp() {
  std::string ip = GetLocalAddress();
  if (ip.empty()) {
    return 0;
  }

  std::vector<std::string> digits = absl::StrSplit(ip, '.');

  int i = 3;
  uint32_t nResult = 0;
  for (auto& digit : digits) {
    auto n = std::stoul(digit);
    nResult |= static_cast<uint32_t>(n) << (8 * i--);
  }

  return nResult;
}

}  // namespace arocketmq
