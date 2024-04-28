.macro print_char %src
  mv a0, %src
  li a7, 11
  ecall
.end_macro

.macro my_macro %dst
    li a1, 3
    li a2, 0
    my_label:
        print_char %dst
        addi a1, a1, -1
        bne a1, a2, my_label
.end_macro

main:
    li t1, 3
    li t2, 0
    li s0, 'A'
    my_label:
    addi s0, s0, 1
        print_char s0
        addi t1, t1, -1
        bne t1, t2, my_label
    my_macro s0
    li t3, 'A'
    print_char t3
