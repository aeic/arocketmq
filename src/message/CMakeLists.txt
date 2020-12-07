target_sources(
  arocketmq-common
  PUBLIC message_const.h
         message_sys_flag.h
         "message.h"
         message_impl.h
         message_accessor.h
         message_client_id_setter.h
         message_ext.h
         message_ext_impl.h
  PRIVATE message_impl.cpp message_client_id_setter.cpp message_ext_impl.cpp)
