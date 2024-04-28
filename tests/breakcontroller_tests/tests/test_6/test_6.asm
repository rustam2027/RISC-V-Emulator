li a1, 0
li a2, 3
start:
    ebreak
    addi a1, a1, 1
    blt a1, a2, start
