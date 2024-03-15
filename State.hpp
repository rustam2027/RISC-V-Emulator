#pragma once
#include "consts.hpp"
#include "Register.hpp"


struct State {
  int* registers;
  int* stack;
  State(){
    registers = new int[AMOUNT_REGISTERS];
    registers[zero] = 0;
  }

  ~State(){
    delete[] registers;
  }
};
