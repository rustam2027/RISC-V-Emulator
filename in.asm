.section .data
hello:
  .string "Hello world!"

.section .text

.macro print_char %src
  mv a0, %src
  li a7, 11
  ecall
.end_macro

li a6, -8

loop_2:
  ebreak
  addi a6, a6, 8

main:
  la a2, hello
  add a2, a2, a6
  lw a1, 0(a2)
  li a5, 56

loop:
  li a3, 0xFF
  sll a3, a3, a5
  and a0, a1, a3
  srl a0, a0, a5
  beqz a0, end
  print_char a0
  addi a5, a5, -8
  blt a5, zero, loop_2
  j loop

end:

  

  

