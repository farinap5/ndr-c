#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

int expression_low(Lexer l);
int expression_high(Lexer l);
int factor(Lexer l);

Token t;
char *addr_matrix[32];

// This matrix includes data placed in address section.
// There were address are declared.
char *data_addr_matrix[32];
// This matrix includes data placed in address declared.
char *instruction_matrix[100];

// Index used of the matrix above when creating new entries.
int imm = 0; //

int im = 0;  //
int ii = 0;  // 
int fs = 0;  // firt instruction
int label_index = 1;

// The data address, where data are stored
// If instructions are overwriting data section
// increse this number
int data_addr = 192;

int parser_expression(Lexer l) {
  t = lexi(l);

  if (lexer_get_type(t) == L_NOP) {
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
  Validate expression of less significance
  + and -
*/
int expression_low(Lexer l) {

  expression_high(l);
  if (lexer_get_type(t) == L_PLUS || lexer_get_type(t) == L_MINUS) {
    int aux1, aux2 = 0;
    Token old = t;
    t = lexi(l);
    expression_low(l);
    
    switch (lexer_get_type(old)) {
    case L_PLUS:
      printf("Symbol +\n");
      aux1 = im-- -1;
      aux2 = im-- -1;
      
      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    LDA $add%d\n", aux2);
      fs++;

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    ADD $add%d\n", aux1);

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    STA $add%d\n\n", aux2);
      im++;

      break;
    case L_MINUS:
      printf("Symbol -\n");
      aux1 = im-- -1;
      aux2 = im-- -1;
      
      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    LDA $add%d\n", aux2);

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    NOT\n");
      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    ADD $add%d\n", aux1);
      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    NOT\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    STA $add%d\n\n", aux2);
      im++;
      break;
    }
  }
}

/*
  Validate expression of high significance
  * and /
*/
int expression_high(Lexer l) {
  parentesis(l);
  if (lexer_get_type(t) == L_ASTERISK || lexer_get_type(t) == L_SLASH) {
    int aux1,aux2 = 0;
    Token old = t;
    t = lexi(l);
    expression_high(l);
    
    switch (lexer_get_type(old)) {
    case L_ASTERISK:
      printf("Symbol *\n");
      aux1 = im-- -1;
      aux2 = im-- -1;

      int aux_lb1 = label_index++;
      int aux_lb2 = label_index++;

      
      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    :p%d\n", aux_lb1);

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    LDA fc\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    ADD $add%d\n", aux2);

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    STA fc\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    LDA fa\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    ADD fb\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    STA fa\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    NOT\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    ADD $add%d\n", aux1);

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    JN :p%d\n", aux_lb2);

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    JMP :p%d\n", aux_lb1);

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    :p%d\n", aux_lb2);

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    STA fa\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    LDA fc\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    STA $add%d\n", aux2);

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    LDA fd\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    STA fa\n");

      instruction_matrix[ii] = (char *)malloc(16 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    STA fc\n");

      instruction_matrix[ii] = (char *)malloc(20 * sizeof(char));
      sprintf(instruction_matrix[ii++],"    LDA $add%d\n\n", aux2);

      im++;      
      break;
    case L_SLASH:
      printf("Symble /\n");
      break;
    }
  } 
}

int parentesis(Lexer l) {
  if (lexer_get_type(t) == L_OPEN) {
    t = lexi(l);
    expression_low(l);
    if (lexer_get_type(t) != L_CLOSE) {
      printf("no close statement");
      return 0;
    }
  } else {
    factor(l);
  }
}

int factor(Lexer l) {
  if (lexer_get_type(t) == L_DIGIT) {
    printf("Write %d to addr %d\n", atoi(lexer_get_symbol(t)), data_addr + imm);
    // Write data to the memory address reserverd after this instruction
    addr_matrix[imm] = (char *)malloc(13 * sizeof(char));
    sprintf(addr_matrix[imm],"    %02x $add%d\n",atoi(lexer_get_symbol(t)), imm);

    // Reserve a new memory address
    data_addr_matrix[imm] = (char *)malloc(13 * sizeof(char));
    sprintf(data_addr_matrix[imm],"    %02x $add%d\n", data_addr + imm, imm);

    imm++;
    im++;
    t = lexi(l);
  }
}

void parser_save(char *outfname) {
  FILE *f = fopen(outfname,"w");

  fwrite("ADDR\n", 5, sizeof(char), f);
    for (int i = 0; i < 32; i++) {
      if (data_addr_matrix[i] != NULL)
        fwrite(data_addr_matrix[i], 13, sizeof(char), f);
        free(data_addr_matrix[i]);
    }
  fwrite("END\n\n", 5, sizeof(char), f);


  fwrite("DATA\n", 5, sizeof(char), f);
  // These bytes are defined and used when running loops when mul is called.
  fwrite("    0 fa\n", 9, sizeof(char), f);
  fwrite("    1 fb\n", 9, sizeof(char), f);
  fwrite("    0 fc\n", 9, sizeof(char), f);
    for (int i = 0; i < 32; i++) {
      if (addr_matrix[i] != NULL)
        fwrite(addr_matrix[i], 13, sizeof(char), f);
        free(addr_matrix[i]);
    }
  fwrite("END\n\n", 5, sizeof(char), f);


  fwrite("TEXT\n", 5, sizeof(char), f);
    for (int i = 0; i < 100; i++) {
      if (instruction_matrix[i] != NULL)
        fwrite(instruction_matrix[i], strlen(instruction_matrix[i]), sizeof(char), f);
        free(instruction_matrix[i]);
    }
  fwrite("END\n", 4, sizeof(char), f);

  fclose(f);
}