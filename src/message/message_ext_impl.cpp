/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "message_ext_impl.h"

#include "message_client_id_setter.h"
#include "util/network.h"
#include "util/string.h"

namespace arocketmq {

// ============================
// MessageExtImpl
// ============================

MessageExtImpl::MessageExtImpl() : MessageExtImpl(0, 0, nullptr, 0, nullptr, kStrEmpty) {}

MessageExtImpl::MessageExtImpl(int queue_id,
                               int64_t born_timestamp,
                               const struct sockaddr* born_host,
                               int64_t store_timestamp,
                               const struct sockaddr* store_host,
                               xlib::xstring msg_id)
    : store_size_(0),
      body_crc_(0),
      queue_id_(queue_id),
      queue_offset_(0),
      commit_log_offset_(0),
      sys_flag_(0),
      born_timestamp_(born_timestamp),
      born_host_(nullptr),
      store_timestamp_(store_timestamp),
      store_host_(nullptr),
      reconsume_times_(3),
      prepared_transaction_offset_(0),
      msg_id_(msg_id) {
  born_host_ = CopySocketAddress(born_host_, born_host);
  store_host_ = CopySocketAddress(store_host_, store_host);
}

MessageExtImpl::~MessageExtImpl() {
  free(born_host_);
  free(store_host_);
}

// TopicFilterType MessageExtImpl::parseTopicFilterType(int32_t sysFlag) {
//   if ((sysFlag & MessageSysFlag::MULTI_TAGS_FLAG) == MessageSysFlag::MULTI_TAGS_FLAG) {
//     return MULTI_TAG;
//   }
//   return SINGLE_TAG;
// }

int32_t MessageExtImpl::store_size() const {
  return store_size_;
}

void MessageExtImpl::set_store_size(int32_t store_size) {
  store_size_ = store_size;
}

int32_t MessageExtImpl::body_crc() const {
  return body_crc_;
}

void MessageExtImpl::set_body_crc(int32_t body_crc) {
  body_crc_ = body_crc;
}

int32_t MessageExtImpl::queue_id() const {
  return queue_id_;
}

void MessageExtImpl::set_queue_id(int32_t queue_id) {
  queue_id_ = queue_id;
}

int64_t MessageExtImpl::queue_offset() const {
  return queue_offset_;
}

void MessageExtImpl::set_queue_offset(int64_t queue_offset) {
  queue_offset_ = queue_offset;
}

int64_t MessageExtImpl::commit_log_offset() const {
  return commit_log_offset_;
}

void MessageExtImpl::set_commit_log_offset(int64_t physic_offset) {
  commit_log_offset_ = physic_offset;
}

int32_t MessageExtImpl::sys_flag() const {
  return sys_flag_;
}

void MessageExtImpl::set_sys_flag(int32_t sys_flag) {
  sys_flag_ = sys_flag;
}

int64_t MessageExtImpl::born_timestamp() const {
  return born_timestamp_;
}

void MessageExtImpl::set_born_timestamp(int64_t bornTimestamp) {
  born_timestamp_ = bornTimestamp;
}

const struct sockaddr* MessageExtImpl::born_host() const {
  return born_host_;
}

void MessageExtImpl::set_born_host(const struct sockaddr* born_host) {
  born_host_ = CopySocketAddress(born_host_, born_host);
}

int64_t MessageExtImpl::store_timestamp() const {
  return store_timestamp_;
}

void MessageExtImpl::set_store_timestamp(int64_t store_timestamp) {
  store_timestamp_ = store_timestamp;
}

const struct sockaddr* MessageExtImpl::store_host() const {
  return store_host_;
}

void MessageExtImpl::set_store_host(const struct sockaddr* store_host) {
  store_host_ = CopySocketAddress(store_host_, store_host);
}

xlib::xstring MessageExtImpl::msg_id() const {
  return msg_id_;
}

void MessageExtImpl::set_msg_id(xlib::xstring msg_id) {
  msg_id_ = msg_id;
}

int32_t MessageExtImpl::reconsume_times() const {
  return reconsume_times_;
}

void MessageExtImpl::set_reconsume_times(int32_t reconsume_times) {
  reconsume_times_ = reconsume_times;
}

int64_t MessageExtImpl::prepared_transaction_offset() const {
  return prepared_transaction_offset_;
}

void MessageExtImpl::set_prepared_transaction_offset(int64_t prepared_transaction_offset) {
  prepared_transaction_offset_ = prepared_transaction_offset;
}

// ============================
// ClientMessageExtImpl
// ============================

xlib::xstring ClientMessageExtImpl::msg_id() const {
  const auto& unique_id = MessageClientIDSetter::GetUniqID(*this);
  return unique_id.empty() ? offset_msg_id() : unique_id;
}

void ClientMessageExtImpl::set_msg_id(xlib::xstring msg_id) {
  // DO NOTHING
  // MessageClientIDSetter::SetUniqID(*this);
}

xlib::xstring ClientMessageExtImpl::offset_msg_id() const {
  return MessageExtImpl::msg_id();
}

void ClientMessageExtImpl::set_offset_msg_id(xlib::xstring offset_msg_id) {
  return MessageExtImpl::set_msg_id(offset_msg_id);
}

}  // namespace arocketmq
