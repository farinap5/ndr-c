#include <stdio.h>

#include "lexer.h"

int expression() {

}

int term() {

}

int factor() {
  
}

int parent() {
    /*
      Down expression
    */

    /*
      Match closing Parent
    */
}

int num() {
    return 5;
}

int main() {
  char *d = "(1111 + 5) ";
  token *t = lex(d);

  while (t->Type) {
    t = lex(NULL);

  }
}
