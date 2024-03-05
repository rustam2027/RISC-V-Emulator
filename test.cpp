#include "State.h"
#include "Register.h"
#include "commands/Add.cpp"
#include "commands/Li.cpp"

#include <stdio.h>

int main(){
  State st = State();
  Li f1 = Li{a1, 8};
  f1.exec(st);

  printf("%d %d", st.registers[a1], a1);

  return 0;
}
