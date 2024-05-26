#include <cassert>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "../frontend/Parser.hpp"
#include "../exceptions/ParserException.hpp"
#include "../exceptions/EmulatorException.hpp"
#include "../State.hpp"
#include "../instructions/instructions.hpp"


void test_li_1() {
  State state;

  Li f = Li({"a1", "8"});
  f.exec(state);

  assert(state.registers[a1] == 8);
  printf("Test li_1 passed!\n");
}


void test_li_2() {
  State state;
  Li f = Li({"zero", "8"});
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test li_2 passed!\n");
}

void test_add_1() {
  State state;
  Li f1 = Li({"a1", "1"});
  Li f2 = Li({"a1", "1"});

  f1.exec(state);
  f2.exec(state);
  
  Add f = Add({"a0", "a1", "a2"});
  f.exec(state);
  printf("Test add_1 passed!\n");
}

void test_add_2() {
  State state;
  Li f1 = Li({"a1", "1"});
  Li f2 = Li({"a2", "2"});

  f1.exec(state);
  f2.exec(state);
  
  Add f = Add({"zero", "a1", "a2"});
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test add_2 passed!\n");
}

void test_mv_1() {
  State state;
  Li f1 = Li({"a1", "1"});
  Li f2 = Li({"a2", "2"});

  f1.exec(state);
  f2.exec(state);
  
  Mv f = Mv({"a1", "a2"});
  f.exec(state);

  assert(state.registers[a1] == state.registers[a2]);
  printf("Test mv_1 passed!\n");
}

void test_mv_2() {
  State state;
  Li f1 = Li({"a1", "1"});

  f1.exec(state);
  
  Mv f = Mv({"a1", "zero"});
  f.exec(state);

  assert(state.registers[a1] == 0);
  printf("Test mv_2 passed!\n");
}

void test_mv_3() {
  State state;
   Li f1 = Li({"a1", "1"});

  f1.exec(state);
  
  Mv f = Mv({"zero", "a1"});
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test mv_3 passed!\n");
}

void test_addi_1() {
  State state;
  Li f1 = Li({"a0", "8"});
  f1.exec(state);
  
  Addi f = Addi({"a1", "a0", "5"});
  f.exec(state);

  assert(state.registers[a1] == 13);
  printf("Test addi_1 passed!\n");

}

void test_addi_2() {
  State state;
  Li f1 = Li({"a0", "8"});
  f1.exec(state);
  
  Addi f = Addi({"zero", "a0", "5"});
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test addi_2 passed!\n");

}

void test_and_1() {
  State state;
  Li f1 = Li({"a0", "187"});
  Li f2 = Li({"a1", "135"});
  f1.exec(state);
  f2.exec(state);

  And f = And({"a3", "a0", "a1"});
  f.exec(state);

  assert(state.registers[a3] == 131);
  printf("Test and_1 passed!\n");

}

void test_and_2() {
  State state;
  Li f1 = Li({"a0", "187"});
  f1.exec(state);

  And f = And({"a1", "a0", "a0"});
  f.exec(state);

  assert(state.registers[a1] == 187);
  printf("Test and_2 passed!\n");
}

void test_and_3() {
  State state;
  Li f1 = Li({"a0", "187"});
  Li f2 = Li({"a1", "135"});
  f1.exec(state);
  f2.exec(state);

  And f = And({"zero", "a0", "a1"});
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test and_3 passed!\n");

}

void test_or_1() {
  State state;
  Li f1 = Li({"a0", "187"});
  Li f2 = Li({"a1", "135"});
  f1.exec(state);
  f2.exec(state);

  Or f = Or({"a3", "a0", "a1"});
  f.exec(state);

  assert(state.registers[a3] == 191);
  printf("Test or_1 passed!\n");

}

void test_or_2() {
  State state;
  Li f1 = Li({"a0", "187"});
  f1.exec(state);

  Or f = Or({"a3", "a0", "a0"});
  f.exec(state);

  assert(state.registers[a3] == 187);
  printf("Test or_2 passed!\n");

}

void test_or_3() {
  State state;
  Li f1 = Li({"a0", "187"});
  Li f2 = Li({"a1", "135"});
  f1.exec(state);
  f2.exec(state);

  Or f = Or({"zero", "a0", "a1"});
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test or_3 passed!\n");

}

void test_sub_1() {
  State state;
  Li f1 = Li({"a1", "1"});
  Li f2 = Li({"a2", "2"});

  f1.exec(state);
  f2.exec(state);

  Sub f = Sub({"a3", "a2", "a1"});
  f.exec(state);

  assert(state.registers[a3] == 1);
  printf("Test sub_1 passed!\n");

}

void test_sub_2() {
  State state;
  Li f1 = Li({"a1", "1"});
  Li f2 = Li({"a2", "2"});

  f1.exec(state);
  f2.exec(state);

  Sub f = Sub({"a3", "a1", "a2"});
  f.exec(state);

  assert(state.registers[a3] == -1);
  printf("Test sub_2 passed!\n");

}

void test_sub_3() {
  State state;
  Li f1 = Li({"a1", "1"});
  Li f2 = Li({"a2", "2"});

  f1.exec(state);
  f2.exec(state);

  Sub f = Sub({"zero", "a1", "a2"});
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test sub_3 passed!\n");
}

void test_sll_1() {
  State state;
  Li f1 = Li({"a1", "170"});
  Li f2 = Li({"a2", "1"});

  f1.exec(state);
  f2.exec(state);

  SLL f = SLL({"a3", "a1", "a2"});
  f.exec(state);

  assert(state.registers[a3] == 340);
  printf("Test sll_1 passed!\n");

}

void test_sll_2() {
  State state;
  Li f1 = Li({"a1", "170"});
  Li f2 = Li({"a2", "12"});

  f1.exec(state);
  f2.exec(state);

  SLL f = SLL({"zero", "a1", "a2"});
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test sll_2 passed!\n");

}

void test_slli_1() {
  State state;
  Li f1 = Li({"a1", "170"});

  f1.exec(state);
  

  SLLI f = SLLI({"a3", "a1", "1"});
  f.exec(state);

  assert(state.registers[a3] == 340);
  printf("Test slli_1 passed!\n");

}

void test_srl_1() {
  State state;
  Li f1 = Li({"a1", "24"});
  Li f2 = Li({"a2", "1"});

  f1.exec(state);
  f2.exec(state);

  SRL f = SRL({"a3", "a1", "a2"});
  f.exec(state);

  assert(state.registers[a3] == 12);
  printf("Test srl_1 passed!\n");

}

void test_srl_2() {
  State state;
  Li f1 = Li({"a1", "24"});
  Li f2 = Li({"a2", "1"});

  f1.exec(state);
  f2.exec(state);

  SRL f = SRL({"zero", "a1", "a2"});
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test srl_2 passed!\n");

}

void test_xor_1() {
  State state;
  Li f1 = Li({"a1", "24"});
  Li f2 = Li({"a2", "2"});

  f1.exec(state);
  f2.exec(state);

  Xor f = Xor({"a3", "a1", "a2"});
  f.exec(state);

  assert(state.registers[a3] == 26);
  printf("Test xor_1 passed!\n");

}

void test_xor_2() {
  State state;
  Li f1 = Li({"a1", "24"});
  Li f2 = Li({"a2", "2"});

  f1.exec(state);
  f2.exec(state);

  Xor f = Xor({"zero", "a1", "a2"});
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test xor_2 passed!\n");
}

void test_sb_1() {
  State state;
  Li f1 = Li({"a1", "10"});
  Li f2 = Li({"a2", "2"});

  f1.exec(state);
  f2.exec(state);

  Sb f = Sb({"a1", "4(a2)"});
  f.exec(state);
  assert(state.stack[2 + 4] == (std::byte) 10);
  printf("Test sb_1 passed!\n");
}

void test_sh_1() {
  State state;
  Li f1 = Li({"a1", "1024"});
  Li f2 = Li({"a2", "2"});

  f1.exec(state);
  f2.exec(state);

  Sh f = Sh({"a1", "4(a2)"});
  f.exec(state);
  assert(state.stack[2 + 4] == (std::byte) (1024 & 0xFF));
  assert(state.stack[2 + 5] == (std::byte) ((1024 >> 8) & 0xFF));
  printf("Test sh_1 passed!\n");
}

void test_sw_1() {
  State state;
  Li f1 = Li({"a1", "33554432"});
  Li f2 = Li({"a2", "2"});

  f1.exec(state);
  f2.exec(state);

  Sw f = Sw({"a1", "4(a2)"});
  f.exec(state);
  assert(state.stack[2 + 4 + 0] == (std::byte) (33554432 & 0xFF));
  assert(state.stack[2 + 4 + 1] == (std::byte) ((33554432 >> 8) & 0xFF));
  assert(state.stack[2 + 4 + 2] == (std::byte) ((33554432 >> 16) & 0xFF));
  assert(state.stack[2 + 4 + 3] == (std::byte) ((33554432 >> 24) & 0xFF));
  printf("Test sw_1 passed!\n");
}

void test_lb_1() {
  State state;
  Li f1 = Li({"a1", "13"});
  Li f2 = Li({"a2", "2"});
  
  f1.exec(state);
  f2.exec(state);

  state.stack[2 + 4] = (std::byte) 13;
  Lb f = Lb({"a3", "4(a2)"});
  f.exec(state);
  assert(state.registers[a3] == 13);
  printf("Test lb_1 passed!\n");

}

void test_lh_1() {
  State state;
  Li f1 = Li({"a1", "1024"});
  Li f2 = Li({"a2", "2"});
  
  f1.exec(state);
  f2.exec(state);

  state.stack[2 + 4] = (std::byte) (1024 & 0xFF);
  state.stack[2 + 4 + 1] = (std::byte) ((1024 >> 8) & 0xFF);
  state.stack[2 + 4 + 2] = (std::byte) 0;
  state.stack[2 + 4 + 3] = (std::byte) 0;
  Lh f = Lh({"a3", "4(a2)"});
  f.exec(state);
  assert(state.registers[a3] == 1024);
  printf("Test lh_1 passed!\n");

}

void test_lw_1() {
  State state;
  Li f1 = Li({"a2", "2"});
  
  f1.exec(state);

  long num = LONG_MAX;

  state.stack[2 + 4] = (std::byte) (num & 0xFF);
  state.stack[2 + 4 + 1] = (std::byte) ((num >> 8) & 0xFF);
  state.stack[2 + 4 + 2] = (std::byte) ((num >> 16) & 0xFF);
  state.stack[2 + 4 + 3] = (std::byte) ((num >> 24) & 0xFF);
  state.stack[2 + 4 + 4] = (std::byte) ((num >> 32) & 0xFF);
  state.stack[2 + 4 + 5] = (std::byte) ((num >> 40) & 0xFF);
  state.stack[2 + 4 + 6] = (std::byte) ((num >> 48) & 0xFF);
  state.stack[2 + 4 + 7] = (std::byte) ((num >> 56) & 0xFF);

  Lw f = Lw({"a3", "4(a2)"});
  f.exec(state);
  assert(state.registers[a3] == num);
  printf("Test lw_1 passed!\n");
}

/* 
void test_ecall_print_int() {
  State state;
  Li f1 = Li{a0, 15};
  Li f2 = Li{a7, 1};

  f1.exec(state);
  f2.exec(state);

  Ecall f = Ecall();
  f.exec(state);
  
}

void test_ecall_read_int() {
  State state;
  Li f1 = Li{a7, 5};

  f1.exec(state);

  Ecall f = Ecall();
  f.exec(state);
  printf("%d", state.registers[a0]);
}

void test_ecall_exit_0() {
  State state;
  Li f1 = Li{a7, 10};

  f1.exec(state);

  Ecall f = Ecall();
  f.exec(state);
}

void test_ecall_exit() {
  State state;
  Li f1 = Li{a7, 93};
  Li f2 = Li{a0, 15};

  f1.exec(state);
  f2.exec(state);

  Ecall f = Ecall();
  f.exec(state);
}

void test_ecall_print_char() {
  State state;
  Li f1 = Li{a0, 65};
  Li f2 = Li{a7, 11};

  f1.exec(state);
  f2.exec(state);

  Ecall f = Ecall();
  f.exec(state);
  
}

*/


void test_all() {
  try
  {
    test_li_1();
    test_li_2();

    test_add_1();
    test_add_2();

    test_mv_1();
    test_mv_2();
    test_mv_3();

    test_addi_1();
    test_addi_2();

    test_and_1();
    test_and_2();
    test_and_3();

    test_or_1();
    test_or_2();
    test_or_3();

    test_sub_1();
    test_sub_2();
    test_sub_3();

    test_sll_1();
    test_sll_2();

    test_slli_1();

    test_srl_1();
    test_srl_2();

    test_xor_1();
    test_xor_2();

    test_sb_1();
    test_sh_1();
    test_sw_1();

    test_lb_1();
    test_lh_1();
    test_lw_1();

    
  }
  catch (const EmulatorException& e)
  {
    std::cerr << e.get_message() << '\n';
  }
  

  // test_ecall_print_int();
  // test_ecall_read_int();
  // test_ecall_exit_0();
  // test_ecall_exit();
  // test_ecall_print_char();
  printf("All tests passed!\n");
}

