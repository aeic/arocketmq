#include "storage/default_message_store.h"

using namespace arocketmq;

int main() {
  DefaultMessageStroe message_store{fs::path{"/Users/james/store"}, 1024 * 1024 * 1024};

  message_store.Load();

  return 0;
}
