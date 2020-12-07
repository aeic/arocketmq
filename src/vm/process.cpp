#include "process.h"

#ifndef WIN32
#include <unistd.h>  // getpid
#else
#include <processthreadsapi.h>
#endif

namespace arocketmq {

int GetPid() {
#ifndef WIN32
  return ::getpid();
#else
  return ::GetCurrentProcessId();
#endif
}

}  // namespace arocketmq
