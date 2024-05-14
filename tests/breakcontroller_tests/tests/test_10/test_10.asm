jal ra, func_1
j endl



func_1:
  sw ra, 0(sp)
  li a1, 12
  jal ra, func_2
  ebreak
  lw ra, 0(sp)
  ret

func_2:
  li a2, 10
  ret

endl:
