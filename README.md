# RISC-V-Emulator
Emulator for RISC V assembler

## Plan
  1. Support all instructions used in the assembly language course:

>* Basic system calls
>* Simple instructions:
>	  * mv
 >   * li
 >   * Math operations
 >   * addi
 >   * Logical operations
 >  * NSS instructions:
 >    * j
 >    * bgt, beq, bez, etc...
 >    * labels
 >  * Stack functions:
 >    * lw
 >    * sw
 >  * Functions (*Optional*):
 >    * call
 >    * ret
 >  * Macro, Comments (*Optional*)

  2. Debug

 >  - Support break points
 >  - Get request from user and answer
 >    - Basic
 >      - conitnue (go to the next breakpoint)
 >      - show registers
 >    - Advanced
 >      - show stack
 >      - enter line and break on it (*Optional*)
 >  - Step by step

  3. Visual

 > - Fix **issues** from Ugliansky
 >    - Delete _in.parse
 >    - Merge BreakController
 >    - Delete ebreak ;(
 >    - e.t.c
 > - Support **memory**
 > - Make some **tui**
 > - Implement **step over** command

    Maybe some pseudo graphics

## Architecture

  0. PreProcessor
  1. Parser 
  2. Interpreter 
  3. Debuger
  4. View?  

### Check ASCII_ART.txt!

## Milestones

  1. Good basic part
  2. Debug
  3. Visual (*OPTIONAL*)

## Check our DIAGRAM.txt
