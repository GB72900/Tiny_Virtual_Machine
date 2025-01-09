<h1>Tiny Virtual Machine</h1>

<h2>Description</h2>
This program is a simple simulation of a Tiny Harvard Architecture machine. It reads a set of instructions
from a file and executes them, simulating the behavior of a basic processor. The simulation includes an
instruction register, program counter, instruction memory, data memory, and an accumulator.
<br />

<h2> Opcode mnemonic meaning </h2>

`01 LOAD X A <- DM[X]`  
`02 ADD X A <- A + DM[X]`  
`03 STORE X DM[X] <- A`  
`04 SUB X A <- A - DM[X]`  
`05 IN X A <- input value`  
`06 OUT X output value of A`  
`07 END X end of program`  
`08 JMP X jump to instruction at X`  
`09 SKIPZ X skip next instruction if A`



<h2>Languages and Utilities Used</h2>
C
<h2>To Compile </h2>

**`gcc HW4.c`**  
**`./HW4 elf.txt`**
