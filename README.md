# CS530 Assignment 2 README

Welcome to the SIC/XE assembler

If the environment allows script to be run, in Linux

* `cd /src`
* `./run_this.sh`
* Proceeds to type multiple arguments separated by spaces

Else, type `make` and then `./assemble + [multiple arguments]` 

This assembler uses `struct`, and `typedef` to construct the different tables of the assembler, from the register table, to the symbol table 

Utility files consists of many functions that is useful in the construction of the assmebled program both in pass1 and pass2

After this project, significant improvement in understanding the SIC/XE machine architecture, how the assembler performs each function both in pass1 and pass2. Gain an understanding of constructing the different files that assembler requires both in pass1 and pass2

| `src` folder | `tests` folder | `ERROR` | `INTERMEDIATE` | `SYMTAB` |
|--------------|----------------|---------|----------------|----------|
| main.cpp     | P2T0.sic       | P2T0.e  |     P2T0.i     |  P2T0.st |
| makefile     | P2T1.sic       | P2T1.e  |     P2T1.i     |  P2T1.st |
| Pass1.cpp    | P2T2.sic       | P2T2.e  |     P2T2.i     |  P2T2.st |
| Pass1.h      | P2T3.sic       | P2T3.e  |     P2T3.i     |  P2T3.st |
| Pass2.cpp    |                |         |                |          |
| Pass2.h      |                |         |                |          |
| run_this.sh  |                |         |                |          |
| tables.cpp   |                |         |                |          |
| tables.h     |                |         |                |          |
| utility.cpp  |                |         |                |          |
| utility.h    |                |         |                |          |

## Sources

1. [Source 1](https://github.com/SaraAnwar97/SIC-XE-Assembler/tree/master)
2. [Source 2](https://github.com/cppcoders/SIC-XE-Assembler)
3. [Source 3](https://github.com/MazenTarek7/SIC-XE-Assembler)
4. [Source 4](https://github.com/nadamostafa98/SIC-XE-Assembler)