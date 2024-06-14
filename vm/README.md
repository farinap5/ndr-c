# Neander Virtual Machine Simulator

Help Menu

```
-- Neader Virtual Machine --

-h, --help     Shows the help menu
-f, --file     May be used to set the filename with instructions
   Use `-f program.mem` (default: ndr-test.mem)
-p, --pc       Configure prog counter register (use decimal)
   Use `-p 10` (default: 0)
-a, --ac       Configure accumulator register (use decimal)
   Use `-a 10` (default: 0)
```

When running the machine using high verbose mode, many lines will go to the output for debugging. Each two lines refer to the state of the machine for that cicle. The frist line presents the memory, the place where `pc` is pointing to, adn its surrouding bytes. The second line shows the registers and the instruction in assembly.

```
20 80 10 81 <30> 81 40 80 50 
PC: 04  AC: 10 | ADD 10 from addr 81
```

The lines above show that `pc` points to the 4th byte (starting from 0), we have a snapshot of the memory and the structions.

Use `main -f dump.mem` for default running mode.


```
~$ ./main -f dump.mem
-- Neader Virtual Machine --

AC: 00   PC: 00

<20> 80 10 81 30 81 40 80 50 
PC: 00  AC: 00 | LDA Read 10 from addr 80
20 80 <10> 81 30 81 40 80 50 
PC: 02  AC: 10 | STA Write 10 to 81
20 80 10 81 <30> 81 40 80 50 
PC: 04  AC: 10 | ADD 10 from addr 81
10 81 30 81 <40> 80 50 83 60 
PC: 06  AC: 20 | OR  10 from addr 80
30 81 40 80 <50> 83 60 80 0f 
PC: 08  AC: 30 | AND 00 from addr 83
40 80 50 83 <60> 80 0f 00 00 
PC: 0a  AC: 00 | NOT AC 00 to ffffffff
80 50 83 60 <80> 0f 00 00 90 
PC: 0b  AC: ff | JMP from 0c to 0f
80 0f 00 00 <90> 0a a0 16 00 
PC: 0f  AC: ff | JN  from 10 to 0a
40 80 50 83 <60> 80 0f 00 00 
PC: 0a  AC: ff | NOT AC ff to ffffff00
80 50 83 60 <80> 0f 00 00 90 
PC: 0b  AC: 00 | JMP from 0c to 0f
80 0f 00 00 <90> 0a a0 16 00 
PC: 0f  AC: 00 | JN  Not Negative
00 00 90 0a <a0> 16 00 00 00 
PC: 11  AC: 00 | JZ  from 12 to 16
16 00 00 00 <f0> 00 00 00 00 
PC: 16  AC: 00 | HLT

AC: 00   PC: 00   Z: 01   N: 00
 #    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
00 - 20 80 10 81 30 81 40 80 50 83 60 80 0f 00 00 90 
10 - 0a a0 16 00 00 00 f0 00 00 00 00 00 00 00 00 00 
20 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
30 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
40 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
50 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
60 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
70 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
80 - 10 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
90 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
a0 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
b0 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
c0 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
d0 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
e0 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
f0 - 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
```
