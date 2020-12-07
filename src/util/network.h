#ifndef AROCKETMQ_UTIL_NETWORK_H_
#define AROCKETMQ_UTIL_NETWORK_H_

#include "vm/network.h"

namespace arocketmq {

struct sockaddr* CopySocketAddress(struct sockaddr* dest, const struct sockaddr* src);

std::string GetLocalAddress();

uint32_t GetIp();

}  // namespace arocketmq

#endif  // AROCKETMQ_UTIL_NETWORK_H_
