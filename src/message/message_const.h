#ifndef AROCKETMQ_MESSAGE_MESSAGECONST_H_
#define AROCKETMQ_MESSAGE_MESSAGECONST_H_

#include <xlib/strings/xstring.hpp>

namespace arocketmq {

namespace MessageConst {

const xlib::xstring PROPERTY_KEYS = "KEYS";
const xlib::xstring PROPERTY_TAGS = "TAGS";
const xlib::xstring PROPERTY_WAIT_STORE_MSG_OK = "WAIT";
const xlib::xstring PROPERTY_DELAY_TIME_LEVEL = "DELAY";
const xlib::xstring PROPERTY_RETRY_TOPIC = "RETRY_TOPIC";
const xlib::xstring PROPERTY_REAL_TOPIC = "REAL_TOPIC";
const xlib::xstring PROPERTY_REAL_QUEUE_ID = "REAL_QID";
const xlib::xstring PROPERTY_TRANSACTION_PREPARED = "TRAN_MSG";
const xlib::xstring PROPERTY_PRODUCER_GROUP = "PGROUP";
const xlib::xstring PROPERTY_MIN_OFFSET = "MIN_OFFSET";
const xlib::xstring PROPERTY_MAX_OFFSET = "MAX_OFFSET";

const xlib::xstring PROPERTY_BUYER_ID = "BUYER_ID";
const xlib::xstring PROPERTY_ORIGIN_MESSAGE_ID = "ORIGIN_MESSAGE_ID";
const xlib::xstring PROPERTY_TRANSFER_FLAG = "TRANSFER_FLAG";
const xlib::xstring PROPERTY_CORRECTION_FLAG = "CORRECTION_FLAG";
const xlib::xstring PROPERTY_MQ2_FLAG = "MQ2_FLAG";
const xlib::xstring PROPERTY_RECONSUME_TIME = "RECONSUME_TIME";
const xlib::xstring PROPERTY_MSG_REGION = "MSG_REGION";
const xlib::xstring PROPERTY_TRACE_SWITCH = "TRACE_ON";
const xlib::xstring PROPERTY_UNIQ_CLIENT_MESSAGE_ID_KEYIDX = "UNIQ_KEY";
const xlib::xstring PROPERTY_MAX_RECONSUME_TIMES = "MAX_RECONSUME_TIMES";
const xlib::xstring PROPERTY_CONSUME_START_TIMESTAMP = "CONSUME_START_TIME";
const xlib::xstring PROPERTY_TRANSACTION_PREPARED_QUEUE_OFFSET = "TRAN_PREPARED_QUEUE_OFFSET";
const xlib::xstring PROPERTY_TRANSACTION_CHECK_TIMES = "TRANSACTION_CHECK_TIMES";
const xlib::xstring PROPERTY_CHECK_IMMUNITY_TIME_IN_SECONDS = "CHECK_IMMUNITY_TIME_IN_SECONDS";
const xlib::xstring PROPERTY_INSTANCE_ID = "INSTANCE_ID";
const xlib::xstring PROPERTY_CORRELATION_ID = "CORRELATION_ID";
const xlib::xstring PROPERTY_MESSAGE_REPLY_TO_CLIENT = "REPLY_TO_CLIENT";
const xlib::xstring PROPERTY_MESSAGE_TTL = "TTL";
const xlib::xstring PROPERTY_REPLY_MESSAGE_ARRIVE_TIME = "ARRIVE_TIME";
const xlib::xstring PROPERTY_PUSH_REPLY_TIME = "PUSH_REPLY_TIME";
const xlib::xstring PROPERTY_CLUSTER = "CLUSTER";
const xlib::xstring PROPERTY_MESSAGE_TYPE = "MSG_TYPE";

const xlib::xstring PROPERTY_ALREADY_COMPRESSED_FLAG = "__ALREADY_COMPRESSED__";

const xlib::xstring KEY_SEPARATOR = " ";

}  // namespace MessageConst

}  // namespace arocketmq

#endif  // AROCKETMQ_MESSAGE_MESSAGECONST_H_
