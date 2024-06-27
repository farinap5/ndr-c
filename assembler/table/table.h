#ifndef TABLE_H
#define TABLE_H

typedef unsigned char __uint8_t;
typedef struct kvdb *KVDB;

KVDB DBInit();
int DBAdd(KVDB db, char *key, __uint8_t value);
__uint8_t DBGet(KVDB db, char *key);

#endif // TABLE_H