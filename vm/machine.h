#ifndef MACHINE_H
#define MACHINE_H

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

struct Machine {
  uint8_t mem[256];
  uint8_t ac;
  uint8_t pc;
} typedef Machine;


uint8_t N(Machine *machine) {
  if (machine->ac < 0 || machine->ac > 128)
    return 1;
  return 0;
}

uint8_t Z(Machine *machine) {
  if (machine->ac == 0)
    return 1;
  return 0;
}

void Dump(Machine *m) {
  printf("AC: %02x   PC: %02x   Z: %02x   N: %02x\n", m->ac, m->pc, Z(m), N(m));
  printf(" #    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
  for (int i = 0; i < 16; i++) {
    printf("%02x - ", i * 16);
    for (int j = 0; j < 16; j++) {
      printf("%02x ", m->mem[i * 16 + j]);
    }
    printf("\n");
  }
}

void DumpMemData(Machine *m) {
  int c = 0;
  for (int i = max(m->pc-4, 0); i < m->pc; i++) {
    printf("%02x ", m->mem[i]);
    c++;
  }
  printf("<%02x> ", m->mem[m->pc]);

  int k = min(m->pc + (8-c)+1, 255);
  for (int i = m->pc+1; i < k; i++) {
    printf("%02x ", m->mem[i]);
    c++;
  }
  printf("\n");
}

void STA(Machine *machine) {
  printf(" STA ");
  machine->pc++;
  uint8_t address = machine->mem[machine->pc];
  machine->mem[address] = machine->ac;
  printf("Write %02x to %02x\n",machine->ac, address);
  machine->pc++;
}

void LDA(Machine *machine) {
  printf(" LDA ");
  machine->pc++;
  uint8_t address = machine->mem[machine->pc];
  machine->ac = machine->mem[address];
  printf("Read %02x from addr %02x\n",machine->ac, address);
  machine->pc++;
}

void ADD(Machine *machine) {
  printf(" ADD ");
  machine->pc++;
  uint8_t address = machine->mem[machine->pc];
  machine->ac += machine->mem[address];
  printf("%02x from addr %02x\n",machine->mem[address], address);
  machine->pc++;
}

void OR(Machine *machine) {
  printf(" OR  ");
  machine->pc++;
  uint8_t address = machine->mem[machine->pc];
  machine->ac |= machine->mem[address];
  printf("%02x from addr %02x\n",machine->mem[address], address);
  machine->pc++;
}

void AND(Machine *machine) {
  printf(" AND ");
  machine->pc++;
  uint8_t address = machine->mem[machine->pc];
  machine->ac &= machine->mem[address];
  printf("%02x from addr %02x\n",machine->mem[address], address);
  machine->pc++;
}

void NOT(Machine *machine) {
  printf(" NOT ");
  machine->pc++;
  printf("AC %02x to %02x\n", machine->ac, ~machine->ac);
  machine->ac = ~machine->ac; // or use machine->ac ^= 0xFF;
}

void JMP(Machine *machine) {
  printf(" JMP ");
  machine->pc++;
  printf("from %02x to %02x\n",machine->pc, machine->mem[machine->pc]);
  machine->pc = machine->mem[machine->pc];
}

void JN(Machine *machine) {
  printf(" JN  ");
  machine->pc++;
  if (machine->ac < 0 || machine->ac > 128) {
    printf("from %02x to %02x\n",machine->pc, machine->mem[machine->pc]);
    machine->pc = machine->mem[machine->pc];
  } else {
    printf("Not Negative\n");
    machine->pc++;
  }
}

void JZ(Machine* machine) {
  printf(" JZ  ");
  machine->pc++;
  if (machine->ac == 0xff) {
    printf("from %02x to %02x\n",machine->pc, machine->mem[machine->pc]);
    machine->pc = machine->mem[machine->pc];
  } else {
    printf("  Not Zero\n");
    machine->pc++;
  }
}

int run_machine_code(Machine m, int v) {
  int r = 1;
  int c = 0;
  while (r) {
    c++;
    if (c > 100) 
    /*  
      Keep to avoid breakin everything. 
    */
      break;
    DumpMemData(&m);
    printf("PC: %02x  AC: %02x |", m.pc, m.ac);

    switch (m.mem[m.pc]) {
      case 00:
        m.pc++;
        break;
      case 16: // 0x10
        STA(&m);
        break;
      case 32: // 0x20
        LDA(&m);
        break;
      case 48: // 0x30
        ADD(&m);
        break;
      case 64: // 0x40
        OR(&m);
        break;
      case 80: // 0x50
        AND(&m);
        break;
      case 96: // 0x60
        NOT(&m);
        break;
      case 128: // 0x80
        JMP(&m);
        break;
      case 144: // 0x90
        JN(&m);
        break;
      case 160: // 0xa0
        JZ(&m);
        break;
      case 240: // HLT 0xf0
        printf(" HLT\n");
        r = 0;
        break;
      default:
        printf(" Not A Instruction\n");
        return 1;
    }
  }

  printf("\n");
  Dump(&m);
  return 0;
}

#endif //MACHINE_H