.macro exit %ecode
  li a0, %ecode
  li a7, 93  
  ecall
.end_macro

.macro read_char %dst
  li a0, 0
  li a7, 12
  ecall
  mv %dst, a0
.end_macro

.macro print_char %src
  mv a0, %src
  li a7, 11
  ecall
.end_macro


main:
  li t1, 10
  li t2, 32 
  loop:
  read_char t0
  beq t0, t1, exit

  print_char t2
  print_char t0

  addi t0, t0, 1
  print_char t0
  print_char t2
  j loop

exit:
  exit 0
