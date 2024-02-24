#ifndef MACHINE_H
#define MACHINE_H

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
  if (machine->ac == 0) {
    printf("from %02x to %02x\n",machine->pc, machine->mem[machine->pc]);
    machine->pc = machine->mem[machine->pc];
  } else {
    printf("  Not Zero\n");
    machine->pc++;
  }
}

#endif //MACHINE_H