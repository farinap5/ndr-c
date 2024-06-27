#include "LL.h"
#include "table.h"
#include <stdlib.h>
#include <string.h>

struct kvdb {
  struct Node *initNode;
};

KVDB DBInit() {
  KVDB db = (KVDB)malloc(sizeof db);
  db->initNode = LLInit();
  return db;
}

int DBAdd(KVDB db, char *key, __uint8_t value) {
  return LLAdd(db->initNode, key, value);
}

__uint8_t DBGet(KVDB db, char *key) {
  struct Node *node = LLGet(db->initNode, key);
  return node->value;
}