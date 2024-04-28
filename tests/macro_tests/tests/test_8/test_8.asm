.text
.macro print_char %src
  mv a0, %src
  li a7, 11
  ecall
.end_macro
main:
  li a1, 'A'
  print_char a1

.data
