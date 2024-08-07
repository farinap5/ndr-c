# Neander Machine

This project is a study on compilers. Here, a custom processor architecture is defined, along with a set of custom machine language instructions. In addition to the virtual machine, there is the compiler, which is capable of recognizing and compiling a simple grammar of mathematical expressions.

This project attempts to answer some questions such as:

1. How can I perform certain mathematical expressions without using stack memory and with a very limited set of instructions?
2. How can I generate code from a parser?
3. How can I create an efficient virtual machine?

This project contains:

- Compiler/parser
- Assembler
- Virtual Machine

Create folder `comp` before running _make_ file.

Simple execution:

```bash
make run FILE=equation.mth
```

Clear data under `comp/`.

```bash
make clear
```

You can write expressions like the following: (2 + 3) + 2.

First, the expression passes through the parser, which calls the lexer to collect each token.

The parser may execute the following actions and create the assembly code.

```
Open parentesis
Write 2 to addr 192
Write 3 to addr 193
Symbol +
Close parentesis
Write 2 to addr 194
Symbol +
```

While the parser, using a recursive descent analyzer, creates the tree of operations, it generates the assembly code, which will be compiled afterward.

```
ADDR
    c0 $add0
    c1 $add1
    c2 $add2
END
```

The assembly (with customized syntax) includes several sections. The `ADDR` section contains address mappings, which are arbitrarily defined. In this example, the parser maps the label `$add0` to the address `c0`. Everything stored in `c0` is accessible via the label `$add0`.

```
DATA
    0 fa
    1 fb
    0 fc
    02 $add0
    03 $add1
    02 $add2
END
```

The `DATA` section is where the data is stored for each previusly defined address (variable value). In this example, the value `02` is mapped to the address `$add0`. This means that any operation referencing the label `$add0` will access the value `02`. Similarly, other values are mapped to their respective addresses. It is possible to address instead labes like `0` mapped to `fa`.

```
TEXT
    LDA $add0
    ADD $add1
    STA $add0

    LDA $add0
    ADD $add1
    STA $add0

    HLT
END
```
`TEXT` section has the assembly code. It consumes the addresses or labels. Jump instructions may use labels as well. Take a look at [neander](https://www.inf.ufrgs.br/arq/wiki/doku.php?id=neander) and `ndr-c/assembler/assembler.c` for all instructions.

The order of the sections must be preserved.