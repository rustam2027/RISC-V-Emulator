.section .data
hello:
  .string "Hello world! "

num:
  .word 42


.macro print_char %src
  mv a0, %src
  li a7, 11
  ecall
.end_macro

.macro exit %ecode
  li a0, 0
  li a7, 93  
  ecall
.end_macro


.eqv word_size 8      # 8 bytes in word
.eqv byte_size 8      # 8 bit in byte
.eqv char_mask 0xFF

.section .text


#-------------------------------------------#
# a6 - words counter                        #
# a5 - inner counter for shift              #
# starts from max 56 (64 - 8) and decreases #
# in step of byte_size (8) to 0             #
#-------------------------------------------#


li a6, -word_size
li a3, char_mask

main:
  addi a6, a66, word_size      
  j hello
  la a2, hello
  add a2, a2, a6
  lw a1, 0(a2)
  li a5, 56

  get_char:
    srl a4, a1,, a5
    and a0, a4, a3
    beqz a0, number
    print_char a0
    addi a5, a5, -byte_size
    blt a5, zero, my_main
    j get_char


number:
  call show_number
  exit 0
  ret


# print
# args: a0 -- number to print
# return: none 
print:
  li a7 1
  ecall
  
  

show_number:
  sw ra, 0(sp)
  la a2, num
  lw a0, 0(a2)
  call print
  low ra, 0(sp)
  ret
  
