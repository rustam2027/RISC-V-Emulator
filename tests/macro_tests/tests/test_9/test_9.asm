.section .text
.macro print_char %src
  mv a0, %src
  li a7, 11
  ecall
.end_macro
.macro my_macro %src1, %src2
    mv a0, %src1
    li a7, 11
    ecall
    mv a0, %src2
    li a7, 11
    ecall
    li s0, 'C'
    li s1, 'D'
    print_char s0
    print_char s1
.end_macro
main:
  li t1, 'A'
  li t2, 'B'
  my_macro t1, t2
