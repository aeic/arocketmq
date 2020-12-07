#include "commit_log.h"

#include <absl/strings/str_format.h>

#include "message/message_sys_flag.h"
#include "util/clock.h"
#include "util/network.h"
#include "util/string.h"

namespace arocketmq {

const size_t END_FILE_MIN_BLANK_LENGTH = 4 + 4;

const int32_t MESSAGE_MAGIC_CODE = -626843481;

CommitLog::CommitLog(const fs::path& commit_log_path, size_t mapped_file_size)
    : mapped_file_queue_(commit_log_path, mapped_file_size), max_message_length_(1024 * 1024 * 4) {}

bool CommitLog::Load() {
  bool result = mapped_file_queue_.Load();
  // log.info("load commit log " + (result ? "OK" : "Failed"));
  return result;
}

void CommitLog::RecoverNormally(int64_t max_physic_offset_of_consume_queue) {
  auto& mapped_files = mapped_file_queue_.mapped_files();
  if (!mapped_files.empty()) {
    size_t index = mapped_files.size();
    index = index < 3 ? 0 : index - 3;

    auto* mapped_file = mapped_files[index].get();
    std::unique_ptr<xlib::byte_buffer> byte_buffer(
        new xlib::byte_buffer(mapped_file->mmap_block().data(), mapped_file->mmap_block().length()));
    int64_t process_offset = mapped_file->from_offset();
    int64_t mapped_file_offset = 0;
    for (;;) {
      // TODO
    }
  } else {
  }
}

void CommitLog::RecoverAbnormally(int64_t max_physic_offset_of_consume_queue) {}

void CommitLog::PutMessage(BrokerMessageExtImpl* msg) {
  // TODO: set crc
  // msg->set_body_crc(0);

  auto* mapped_file = mapped_file_queue_.GetLastMappedFile();

  msg->set_store_timestamp(GetCurrentTimeMillis());

  if (nullptr == mapped_file || mapped_file->Full()) {
    mapped_file = mapped_file_queue_.GetLastMappedFile(0);
    if (nullptr == mapped_file) {
      // log.error("create mapped file1 error, topic: " + msg.getTopic() + " clientAddr: " + msg.getBornHostString());
      // return CompletableFuture.completedFuture(new PutMessageResult(PutMessageStatus.CREATE_MAPEDFILE_FAILED, null));
      return;
    }
  }

  mapped_file->AppendData(std::bind(&CommitLog::AppendMessage, this, msg, std::placeholders::_1, std::placeholders::_2,
                                    std::placeholders::_3));
}

void CommitLog::AppendMessage(BrokerMessageExtImpl* msg,
                              int64_t from_offset,
                              xlib::byte_buffer& byte_buffer,
                              size_t max_blank) {
  int64_t wrote_offset = from_offset + byte_buffer.position();

  auto sys_flag = msg->sys_flag();

  size_t born_host_length = (sys_flag & MessageSysFlag::BORNHOST_V6_FLAG) == 0 ? 4 + 4 : 16 + 4;
  size_t store_host_length = (sys_flag & MessageSysFlag::STOREHOST_V6_FLAG) == 0 ? 4 + 4 : 16 + 4;

  // create message id

  auto topic_queue = absl::StrFormat("%s-%d", ToStringView(msg->topic()), msg->queue_id());
  size_t queue_offset = 0;

  // TODO: check transaction flag

  // serialize message
  size_t properties_length = msg->properties_string().length();

  size_t topic_length = msg->topic().length();

  size_t body_length = msg->body().length();

  size_t message_length = CalculateMessageLength(sys_flag, body_length, topic_length, properties_length);

  if (message_length > max_message_length_) {
    // MESSAGE_SIZE_EXCEEDED
  }

  if (message_length + END_FILE_MIN_BLANK_LENGTH > max_blank) {
    // END_OF_FILE
  }

  size_t physical_offset = from_offset + byte_buffer.position();

  // 1 TOTALSIZE
  byte_buffer.put<int32_t>(message_length);
  // 2 MAGICCODE
  byte_buffer.put<int32_t>(MESSAGE_MAGIC_CODE);
  // 3 BODYCRC
  byte_buffer.put<int32_t>(msg->body_crc());
  // 4 QUEUEID
  byte_buffer.put<int32_t>(msg->queue_id());
  // 5 FLAG
  byte_buffer.put<int32_t>(msg->flag());
  // 6 QUEUEOFFSET
  byte_buffer.put<int64_t>(queue_offset);
  // 7 PHYSICALOFFSET
  byte_buffer.put<int64_t>(physical_offset);
  // 8 SYSFLAG
  byte_buffer.put<int32_t>(msg->sys_flag());
  // 9 BORNTIMESTAMP
  byte_buffer.put<int64_t>(msg->born_timestamp());
  // 10 BORNHOST
  // this.resetByteBuffer(bornHostHolder, bornHostLength);
  // byte_buffer.put(msg->getBornHostBytes(bornHostHolder));
  // 11 STORETIMESTAMP
  byte_buffer.put<int64_t>(msg->store_timestamp());
  // 12 STOREHOSTADDRESS
  // this.resetByteBuffer(storeHostHolder, storeHostLength);
  // byte_buffer.put(msg->getStoreHostBytes(storeHostHolder));
  // 13 RECONSUMETIMES
  byte_buffer.put<int32_t>(msg->reconsume_times());
  // 14 Prepared Transaction Offset
  byte_buffer.put<int64_t>(msg->prepared_transaction_offset());
  // 15 BODY
  byte_buffer.put<int32_t>(body_length);
  if (body_length > 0) {
    byte_buffer.put<xlib::xstring>(msg->body());
  }
  // 16 TOPIC
  byte_buffer.put<int8_t>(topic_length);
  byte_buffer.put(msg->topic());
  // 17 PROPERTIES
  byte_buffer.put<int16_t>(properties_length);
  if (properties_length > 0) {
    byte_buffer.put(msg->properties_string());
  }
}

size_t CommitLog::CalculateMessageLength(int sys_flag,
                                         size_t body_length,
                                         size_t topic_length,
                                         size_t properties_length) {
  size_t born_host_length = (sys_flag & MessageSysFlag::BORNHOST_V6_FLAG) == 0 ? 4 + 4 : 16 + 4;
  size_t store_host_length = (sys_flag & MessageSysFlag::STOREHOST_V6_FLAG) == 0 ? 4 + 4 : 16 + 4;
  size_t message_length = 4                        // TOTALSIZE
                          + 4                      // MAGICCODE
                          + 4                      // BODYCRC
                          + 4                      // QUEUEID
                          + 4                      // FLAG
                          + 8                      // QUEUEOFFSET
                          + 8                      // PHYSICALOFFSET
                          + 4                      // SYSFLAG
                          + 8                      // BORNTIMESTAMP
                          + born_host_length       // BORNHOST
                          + 8                      // STORETIMESTAMP
                          + store_host_length      // STOREHOSTADDRESS
                          + 4                      // RECONSUMETIMES
                          + 8                      // Prepared Transaction Offset
                          + 4 + body_length        // BODY
                          + 1 + topic_length       // TOPIC
                          + 2 + properties_length  // propertiesLength
                          + 0;
  return message_length;
}

void CommitLog::PutSocketAddress(xlib::byte_buffer& byte_buffer, const struct sockaddr* sa) {
  if (sa->sa_family == AF_INET) {
    const struct sockaddr_in* sin = (const struct sockaddr_in*)sa;
    byte_buffer.put(&sin->sin_addr, 4, 0, 4);
    byte_buffer.put(&sin->sin_port, 4, 0, 4);
  } else if (sa->sa_family == AF_INET6) {
    const struct sockaddr_in6* sin6 = (const struct sockaddr_in6*)sa;
    byte_buffer.put(&sin6->sin6_addr, 16, 0, 16);
    byte_buffer.put(&sin6->sin6_port, 4, 0, 4);
  }
}

}  // namespace arocketmq
