.macro print_char %src
  mv a0, %src
  li a7, 11
  ecall
.end_macro

.macro my_macro %src
    mv a0, %src
    print_char a0
    print_char %src
.end_macro

main:
  li t0, 'X'
  my_macro t0
