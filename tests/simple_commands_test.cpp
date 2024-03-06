#include <cassert>
#include <cstdio>
#include <stdio.h>

#include "../State.h"

#include "../commands/Li.cpp"
#include "../commands/Add.cpp"


void test_li_1() {
  State state;

  Li f = Li{a1, 8};
  f.exec(state);

  assert(state.registers[a1] == 8);
  printf("Test li_1 passed!\n");
}

void test_add_1() {
  
}

void test_all() {
  test_li_1();
  printf("All tests passed!");
}
