#ifndef AROCKETMQ_VM_NETWORK_H_
#define AROCKETMQ_VM_NETWORK_H_

#include <cstdint>

#include <string>

#ifndef WIN32
#include <arpa/inet.h>
#include <sys/socket.h>
#else
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

namespace arocketmq {

union sockaddr_union {
  struct sockaddr_in sin;
  struct sockaddr_in6 sin6;
};

static inline size_t sockaddr_size(const struct sockaddr* sa) {
  return sa->sa_family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
}

std::string SocketAddress2String(const struct sockaddr* addr);

struct sockaddr* LookupNameServers(const std::string& hostname);

std::string GetLocalHostName();

}  // namespace arocketmq

#endif  // AROCKETMQ_VM_NETWORK_H_
