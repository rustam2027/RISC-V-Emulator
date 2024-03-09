#include <cassert>
#include <cstdio>
#include <stdio.h>

#include "../State.h"
#include "../commands/commands.h"


void test_li_1() {
  State state;

  Li f = Li{a1, 8};
  f.exec(state);

  assert(state.registers[a1] == 8);
  printf("Test li_1 passed!\n");
}

void test_li_2() {
  State state;
  Li f = Li{zero, 8};
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test li_2 passed!\n");
}

void test_add_1() {
  State state;
  Li f1 = Li{a1, 1};
  Li f2 = Li{a2, 2};

  f1.exec(state);
  f2.exec(state);
  
  Add f = Add{a0, a1, a2};
  f.exec(state);

  assert(state.registers[a0] == 3);
  printf("Test add_1 passed!\n");
}

void test_add_2() {
  State state;
  Li f1 = Li{a1, 1};
  Li f2 = Li{a2, 2};

  f1.exec(state);
  f2.exec(state);
  
  Add f = Add{zero, a1, a2};
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test add_2 passed!\n");
}

void test_mv_1() {
  State state;
  Li f1 = Li{a1, 1};
  Li f2 = Li{a2, 2};

  f1.exec(state);
  f2.exec(state);
  
  Mv f = Mv{a1, a2};
  f.exec(state);

  assert(state.registers[a1] == state.registers[a2]);
  printf("Test mv_1 passed!\n");
}

void test_mv_2() {
  State state;
  Li f1 = Li{a1, 1};

  f1.exec(state);
  
  Mv f = Mv{a1, zero};
  f.exec(state);

  assert(state.registers[a1] == 0);
  printf("Test mv_2 passed!\n");
}

void test_mv_3() {
  State state;
  Li f1 = Li{a1, 1};

  f1.exec(state);
  
  Mv f = Mv{zero, a1};
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test mv_3 passed!\n");
}

void test_addi_1() {
  State state;
  Li f1 = Li{a0, 8};
  f1.exec(state);
  
  Addi f = Addi{a1, a0, 5};
  f.exec(state);

  assert(state.registers[a1] == 13);
  printf("Test addi_1 passed!\n");

}

void test_addi_2() {
  State state;
  Li f1 = Li{a0, 8};
  f1.exec(state);
  
  Addi f = Addi{zero, a0, 5};
  f.exec(state);

  assert(state.registers[zero] == 0);
  printf("Test addi_2 passed!\n");

}

void test_all() {
  test_li_1();
  test_li_2();

  test_add_1();
  test_add_2();

  test_mv_1();
  test_mv_2();
  test_mv_3();

  test_addi_1();
  test_addi_2();

  printf("All tests passed!\n");
}
