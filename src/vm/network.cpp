#include "network.h"

#ifndef WIN32
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>  // gethostname
#endif

namespace arocketmq {

thread_local static sockaddr_union sin_buf;

static std::string sLocalHostName;

std::string SocketAddress2String(const struct sockaddr* addr) {
  if (nullptr == addr) {
    return "127.0.0.1";
  }

  char buf[128];
  std::string address;
  uint16_t port = 0;

  if (addr->sa_family == AF_INET) {
    auto* sin = (struct sockaddr_in*)addr;
    if (nullptr != inet_ntop(AF_INET, &sin->sin_addr, buf, sizeof(buf))) {
      address = buf;
    }
    port = ntohs(sin->sin_port);
  } else if (addr->sa_family == AF_INET6) {
    auto* sin6 = (struct sockaddr_in6*)addr;
    if (nullptr != inet_ntop(AF_INET6, &sin6->sin6_addr, buf, sizeof(buf))) {
      address = buf;
    }
    port = ntohs(sin6->sin6_port);
  } else {
    throw std::runtime_error("don't support non-inet Address families.");
  }

  if (!address.empty() && port != 0) {
    if (addr->sa_family == AF_INET6) {
      address = "[" + address + "]";
    }
    address += ":" + std::to_string(port);
  }

  return address;
}

struct sockaddr* LookupNameServers(const std::string& hostname) {
  if (hostname.empty()) {
    return nullptr;
  }

  struct addrinfo hints;
  struct addrinfo* answer = NULL;

  /* Build the hints to tell getaddrinfo how to act. */
  std::memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;     /* v4 or v6 is fine. */
  hints.ai_socktype = SOCK_STREAM; /* We want stream socket*/
  hints.ai_protocol = IPPROTO_TCP; /* We want a TCP socket */
  hints.ai_flags = AI_ADDRCONFIG;  /* Only return addresses we can use. */

  // Look up the hostname.
  int error = ::getaddrinfo(hostname.c_str(), NULL, &hints, &answer);
  if (error != 0) {
    std::string info = "Failed to resolve host name(" + hostname + "): " + ::gai_strerror(error);
    throw std::runtime_error(info.c_str());
  }

  struct sockaddr* sin = nullptr;

  for (struct addrinfo* ai = answer; ai != NULL; ai = ai->ai_next) {
    auto* ai_addr = ai->ai_addr;
    if (ai_addr->sa_family != AF_INET && ai_addr->sa_family != AF_INET6) {
      continue;
    }
    sin = (struct sockaddr*)&sin_buf;
    std::memcpy(sin, ai_addr, sockaddr_size(ai_addr));
    break;
  }

  ::freeaddrinfo(answer);

  return sin;
}

std::string GetLocalHostName() {
  if (sLocalHostName.empty()) {
    char name[1024];
    if (::gethostname(name, sizeof(name)) != 0) {
      return "";
    }
    sLocalHostName.append(name, strlen(name));
  }
  return sLocalHostName;
}

}  // namespace arocketmq
