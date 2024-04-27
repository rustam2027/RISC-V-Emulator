.macro print_char %src
  mv a0, %src
  li a7, 11
  ecall
.end_macro

.macro read_char %dst
  li a0, 0
  li a7, 12
  ecall
  mv %dst, a0
.end_macro

main:
    read_char t0
    print_char t0
    print_char t0

    li t2, 'X'
    print_char t2