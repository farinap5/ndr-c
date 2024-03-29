#include <stdio.h>
#include "lexer.h"

int expression_low(lexer *l);
int expression_high(lexer *l);
int factor(lexer *l);

token *t;
char *addr_matrix[10];
char *data_addr_matrix[10];
char *instruction_matrix[32];
int im = 0;
int ii = 0;
int fs = 0; // firt instruction
int data_addr = 100;



int expression(lexer *l) {
  t = lexi(l);

  if (t->Type == L_NOP) {
    printf("No Token\n");
    return 0;
  }

  expression_low(l);
  lexer_token_free(t);
  
  instruction_matrix[ii] = (char *)malloc(14 * sizeof(char));
  sprintf(instruction_matrix[ii],"    HLT\n");
  ii++;
}

/*
  Validate expression of low significance
  + and -
*/
int expression_low(lexer *l) {

  expression_high(l);
  

  if (t->Type == L_PLUS || t->Type == L_MINUS) {
    token *old = t;
    t = lexi(l);
    expression_low(l);
    
    switch (old->Type) {
    case L_PLUS:
      printf("Symbol +\n");

      if (fs == 0) {
        instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
        sprintf(instruction_matrix[ii++],"    LDA $add%d\n",im-- -1);
        fs++;
      }

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    ADD $add%d\n",im-- -1);

      break;
    case L_MINUS:
      printf("Symbol -\n");
      if (fs == 0) {
        instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
        sprintf(instruction_matrix[ii++],"    LDA $add%d\n",im-- -1);
        fs++;
      }

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    NOT\n");
      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    ADD $add%d\n",im-- -1);
      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    NOT\n");
      break;
    }
  }
}

/*
  Validate expression of high significance
  * and /
*/
int expression_high(lexer *l) {
  
  factor(l);
  if (t->Type == L_ASTERISK || t->Type == L_SLASH) {
    token *old = t;
    t = lexi(l);
    expression_high(l);
    
    switch (old->Type) {
    case L_ASTERISK:
      printf("Symbol *\n");
      break;
    case L_SLASH:
      printf("Symble /\n");
      break;
    }
  } 
}

int factor(lexer *l) {
  if (t->Type == L_DIGIT) {
    printf("Write %d to addr %d\n", atoi(t->Symbol), data_addr + im);
    // Write data to the memory address reserverd after this instruction
    addr_matrix[im] = (char *)malloc(13 * sizeof(char));
    sprintf(addr_matrix[im],"    %02x $add%d\n",atoi(t->Symbol),im);

    // Reserve a new memory address
    data_addr_matrix[im] = (char *)malloc(13 * sizeof(char));
    sprintf(data_addr_matrix[im],"    %02x $add%d\n", data_addr + im, im);

    im++;
    t = lexi(l);
  }
}

void save(char *outfname) {
  FILE *f = fopen(outfname,"w");

  fwrite("ADDR\n", 5, sizeof(char), f);
    for (int i = 0; i < 10; i++) {
      if (data_addr_matrix[i] != NULL)
        fwrite(data_addr_matrix[i], 13, sizeof(char), f);
        free(data_addr_matrix[i]);
    }
  fwrite("END\n\n", 5, sizeof(char), f);


  fwrite("DATA\n", 5, sizeof(char), f);
    for (int i = 0; i < 10; i++) {
      if (addr_matrix[i] != NULL)
        fwrite(addr_matrix[i], 13, sizeof(char), f);
        free(addr_matrix[i]);
    }
  fwrite("END\n\n", 5, sizeof(char), f);


  fwrite("TEXT\n", 5, sizeof(char), f);
    for (int i = 0; i < 10; i++) {
      if (instruction_matrix[i] != NULL)
        fwrite(instruction_matrix[i], strlen(instruction_matrix[i]), sizeof(char), f);
        free(instruction_matrix[i]);
    }
  fwrite("END\n", 4, sizeof(char), f);

  fclose(f);
}
