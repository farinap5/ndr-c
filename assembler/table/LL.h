#ifndef LIST
#define LIST

typedef struct node *Node;
typedef unsigned char __uint8_t;

Node LLInit();
int LLAdd(Node list, const char *key, __uint8_t value);
Node LLGet(Node list, char *key);
void LL_Free(Node list);
__uint8_t LLGet_Value(Node node);

/*int LLDel(struct Node *list, char *key);*/

#endif