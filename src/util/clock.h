#ifndef AROCKETMQ_UTIL_CLOCK_H_
#define AROCKETMQ_UTIL_CLOCK_H_

#include <absl/time/clock.h>

namespace arocketmq {

inline uint64_t GetCurrentTimeMillis() {
  return absl::GetCurrentTimeNanos() / 1000000;
}

}  // namespace arocketmq

#endif  // AROCKETMQ_UTIL_CLOCK_H_
