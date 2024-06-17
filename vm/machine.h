#ifndef MACHINE_H
#define MACHINE_H

typedef unsigned char uint8_t;
typedef struct machine Machine;

uint8_t N(Machine *machine);
uint8_t Z(Machine *machine);
void machine_free(Machine *m);
void Dump(Machine *m);
void DumpMemData(Machine *m);
int run_machine_code(Machine *m, int v);
Machine *machine_init(uint8_t ac, uint8_t pc);
void machine_set_mem(Machine *m, int i, uint8_t data);

#endif // MACHINE_H