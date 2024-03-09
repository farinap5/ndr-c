#pragma once
#ifndef LIST
#define LIST

#include "LL.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  char *key;
  __uint8_t value;
  struct Node *next;
  struct Node *prev;
};

struct Node *LLInit() {
  struct Node *ret = (struct Node *)malloc(sizeof(struct Node));
  ret->key = 0;
  ret->value = 0;
  ret->next = 0;
  ret->prev = 0;
  return ret;
}

int LLAdd(struct Node *list, const char *key, __uint8_t value) {
  size_t keylen = strlen(key);
  if (list == 0) {
    return 1;
  }

  else if (list->key == 0) {
    list->key = (char *)malloc(keylen > 64 ? 64 : keylen);
    strcpy(list->key, key);
    list->value = value;
    return 0;
  }

  struct Node *ret = (struct Node *)malloc(sizeof(struct Node));
  ret->key = (char *)malloc(keylen > 64 ? 64 : keylen);
  ret->next = 0;
  strcpy(ret->key, key);
  ret->value = value;

  struct Node *aux = list;
  while (aux->next != NULL) {
    aux = aux->next;
  }
  aux->next = ret;
  ret->prev = aux;
  return 0;
}

struct Node *LLGet(struct Node *list, char *key) {
  struct Node *aux = list;
  while (aux != NULL) {
    if (strcmp(aux->key, key) == 0) {
      return aux;
    }
    aux = aux->next;
  }
  return 0;
}

/*int LLDel(struct Node *list, char *key) {

}*/

#endif