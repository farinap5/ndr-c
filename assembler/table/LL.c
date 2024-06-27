#include "LL.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char *key;
  __uint8_t value;
  Node next;
  Node *prev;
};

Node LLInit() {
  Node ret = (Node)malloc(sizeof(struct node));
  ret->key = NULL;
  ret->value = 0;
  ret->next = NULL;
  ret->prev = NULL;
  return ret;
}

int LLAdd(Node list, const char *key, __uint8_t value) {
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

  Node ret = (Node)malloc(sizeof ret);
  ret->key = (char *)malloc(keylen > 64 ? 64 : keylen);
  ret->next = 0;
  strcpy(ret->key, key);
  ret->value = value;

  Node aux = list;
  while (aux->next != NULL) {
    aux = aux->next;
  }
  aux->next = ret;
  ret->prev = aux;
  return 0;
}

Node LLGet(Node list, char *key) {
  Node aux = list;
  while (aux != NULL) {
    if (strcmp(aux->key, key) == 0) {
      return aux;
    }
    aux = aux->next;
  }
  return 0;
}


__uint8_t LLGet_Value(Node node) {
    return node->value;
}
/*int LLDel(struct Node *list, char *key) {

}*/