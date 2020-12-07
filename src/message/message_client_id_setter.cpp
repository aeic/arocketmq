#include "message_client_id_setter.h"

#include <cstdlib>
#include <ctime>

#include <atomic>

#include <xlib/system/byte_order.hpp>

#include "util/clock.h"
#include "util/network.h"
#include "util/string.h"
#include "vm/process.h"

namespace arocketmq {

namespace detail {

class MessageClientIDGenerator {
 public:
  MessageClientIDGenerator() {
    std::srand((uint32_t)std::time(NULL));

    uint32_t pid = xlib::to_big_endian(static_cast<uint32_t>(GetPid()));
    uint32_t ip = xlib::to_big_endian(GetIp());
    uint32_t random_num = xlib::to_big_endian(static_cast<uint32_t>(std::rand()));

    char bin_buf[10];
    std::memcpy(bin_buf + 2, &pid, 4);
    std::memcpy(bin_buf, &ip, 4);
    std::memcpy(bin_buf + 6, &random_num, 4);

    fix_string_ = ToHexString(bin_buf, 10);

    SetStartTime(GetCurrentTimeMillis());

    counter_ = 0;
  }

  void SetStartTime(uint64_t millis) {
    // std::time_t
    //   Although not defined, this is almost always an integral value holding the number of seconds
    //   (not counting leap seconds) since 00:00, Jan 1 1970 UTC, corresponding to POSIX time.
    std::time_t tmNow = millis / 1000;
    std::tm* ptmNow = std::localtime(&tmNow);  // may not be thread-safe

    std::tm curMonthBegin = {0};
    curMonthBegin.tm_year = ptmNow->tm_year;  // since 1900
    curMonthBegin.tm_mon = ptmNow->tm_mon;    // [0, 11]
    curMonthBegin.tm_mday = 1;                // [1, 31]
    curMonthBegin.tm_hour = 0;                // [0, 23]
    curMonthBegin.tm_min = 0;                 // [0, 59]
    curMonthBegin.tm_sec = 0;                 // [0, 60]

    std::tm nextMonthBegin = {0};
    if (ptmNow->tm_mon >= 11) {
      nextMonthBegin.tm_year = ptmNow->tm_year + 1;
      nextMonthBegin.tm_mon = 0;
    } else {
      nextMonthBegin.tm_year = ptmNow->tm_year;
      nextMonthBegin.tm_mon = ptmNow->tm_mon + 1;
    }
    nextMonthBegin.tm_mday = 1;
    nextMonthBegin.tm_hour = 0;
    nextMonthBegin.tm_min = 0;
    nextMonthBegin.tm_sec = 0;

    start_time_ = std::mktime(&curMonthBegin) * 1000;
    next_start_time_ = std::mktime(&nextMonthBegin) * 1000;
  }

  std::string CreateUniqueID() {
    uint64_t current = GetCurrentTimeMillis();
    if (current >= next_start_time_) {
      SetStartTime(current);
      current = GetCurrentTimeMillis();
    }

    uint32_t period = xlib::to_big_endian(static_cast<uint32_t>(current - start_time_));
    uint16_t seqid = xlib::to_big_endian(counter_++);

    char bin_buf[6];
    std::memcpy(bin_buf, &period, 4);
    std::memcpy(bin_buf + 4, &seqid, 2);

    return fix_string_ + ToHexString(bin_buf, 6);
  }

 private:
  uint64_t start_time_;
  uint64_t next_start_time_;
  std::atomic<uint16_t> counter_;

  std::string fix_string_;
};

}  // namespace detail

namespace MessageClientIDSetter {

static arocketmq::detail::MessageClientIDGenerator sIdGenerator;

xlib::xstring CreateUniqID() {
  return sIdGenerator.CreateUniqueID();
}

}  // namespace MessageClientIDSetter

}  // namespace arocketmq