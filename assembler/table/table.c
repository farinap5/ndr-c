#include <stdlib.h>
#include <string.h>

#include "LL.h"
#include "table.h"

struct kvdb {
  Node initNode;
};

KVDB DBInit() {
  KVDB db = (KVDB)malloc(sizeof(struct kvdb));
  db->initNode = LLInit();
  return db;
}

int DBAdd(KVDB db, char *key, __uint8_t value) {
  return LLAdd(db->initNode, key, value);
}

__uint8_t DBGet(KVDB db, char *key) {
  Node node = LLGet(db->initNode, key);
  return LLGet_Value(node);
}