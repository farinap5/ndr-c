#pragma once
#include "LL.h"
#include <stdlib.h>
#include <string.h>

struct KVDB {
  struct Node *initNode;
};

struct KVDB DBInit() {
  struct KVDB db;
  db.initNode = LLInit();
  return db;
}

int DBAdd(struct KVDB db, char *key, __uint8_t value) {
  return LLAdd(db.initNode, key, value);
}

__uint8_t DBGet(struct KVDB db, char *key) {
  struct Node *node = LLGet(db.initNode, key);
  return node->value;
}