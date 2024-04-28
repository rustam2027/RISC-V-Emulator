.eqv space 65
.eqv Bb 66
.eqv Cc 67

.macro my_print_char %src
  li a0, %src
  li a7, 11
  ecall
.end_macro

main:
  li t1, space
  my_print_char space
  my_print_char Bb
  my_print_char Cc
  
