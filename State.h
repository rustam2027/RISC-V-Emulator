#pragma once
#include "consts.h"
#include "Register.h"


struct State {
  int* registers;
  State(){
    registers = new int[AMOUNT_REGISTERS];
    registers[zero] = 0;
  }

  ~State(){
    delete[] registers;
  }
};
