#ifndef AROCKETMQ_MESSAGE_MESSAGESYSFLAG_H_
#define AROCKETMQ_MESSAGE_MESSAGESYSFLAG_H_

#include <cstdint>

namespace arocketmq {

namespace MessageSysFlag {

const int32_t COMPRESSED_FLAG = 0x1 << 0;
const int32_t MULTI_TAGS_FLAG = 0x1 << 1;

const int32_t TRANSACTION_NOT_TYPE = 0x0;
const int32_t TRANSACTION_PREPARED_TYPE = 0x1 << 2;
const int32_t TRANSACTION_COMMIT_TYPE = 0x2 << 2;
const int32_t TRANSACTION_ROLLBACK_TYPE = 0x3 << 2;

const int32_t BORNHOST_V6_FLAG = 0x01 << 4;
const int32_t STOREHOST_V6_FLAG = 0x01 << 5;

inline int32_t GetTransactionValue(int32_t flag) {
  return flag & TRANSACTION_ROLLBACK_TYPE;
}

inline int32_t ResetTransactionValue(int32_t flag, int32_t type) {
  return (flag & (~TRANSACTION_ROLLBACK_TYPE)) | type;
}

inline int32_t ClearCompressedFlag(int32_t flag) {
  return flag & (~COMPRESSED_FLAG);
}

}  // namespace MessageSysFlag

}  // namespace arocketmq

#endif  // AROCKETMQ_MESSAGE_MESSAGESYSFLAG_H_
