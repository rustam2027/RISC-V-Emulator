.macro print_char %src
  mv a0, %src
  li a7, 11
  ecall
.end_macro

.macro my_macro %src
    mv a0, %src
    print_char a0
    print_char a0

.end_macro

.macro new_macro %src
    mv a2, %src
    my_macro a2
    my_macro a2
.end_macro

main:
    li a3, 'C'
    new_macro a3