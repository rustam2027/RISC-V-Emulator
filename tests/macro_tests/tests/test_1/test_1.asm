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
    read_char t1
    print_char t1
