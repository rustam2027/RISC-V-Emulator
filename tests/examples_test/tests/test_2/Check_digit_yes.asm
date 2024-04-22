.text
.macro exit %ecode
  li a0, 0
  li a7, 93  
  ecall
.end_macro

.macro read_char %dst
  li a0, 0
  li a7, 12  #syscall 
  ecall
  mv %dst, a0
.end_macro

.macro print_char %src
  mv a0, %src  #print this char
  li a7, 11    #syscall 
  ecall
.end_macro

main:
  read_char t0
  li t1, 0x30 # '0'
  blt t0, t1, exit
  li t1, '9'
  bgt t0, t1, exit
  
  li t1, '1'
  print_char t1
  
exit:
  exit 0
