# RISC-V-Emulator
Emulator for RISC V assembler

## Plan
  1. Support all commands used in the assembly language course
    a. Basic system calls
    b. Simple commands:
      * mv
      * li
      * Math operations
      * addi
      * Logical operations
    c. Labels
    d. Comments
    e. NSS commands:
      * j
      * bgt, beq, bez, etc...
    f. Macro
    g. Stack functions:
      * lw
      * sw
    h. Functions:
      * call
      * ret

  2. Debug
    Step by step debuging and viewing registers and stack

  3. Visual
    Maybe some pseudo graphics

## Architecture
  0. PreProcessor
  1. Parser 
  2. Interpreter 
  3. Debuger
  4. View?  
-------------------------------------------------------------------------------------
|                                                                                   |
|                  ===============     
|    File.asm --->| PreProccessor |
|                  ===============                                                    
|                        |
|                        |
|                        V
|                  - Delete commets 
|                  - Inline Macros 
|                  - CreateLable Dict --->{ name : ptr_on_line }
|                        |
|                        |
|                        V
|                  ==============
|                  |   Parser    |   < ------------- 
|                  ==============                  |
|                        |                         |
|                        | List\[Func\]              |
|                        |                         |
|                        V                         |
|                  ==============                  |
|                  | Interpreter | ---> interpert on:
|                  ==============              - State
|                                              - Registers
|                                              - Stack 
