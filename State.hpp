#pragma once
#include "consts.hpp"
#include "Register.hpp"


struct State {
  int* registers;
  int* stack;
  State(){
    registers = new int[AMOUNT_REGISTERS];
    stack = new int[AMOUNT_STACK];
    registers[zero] = 0;
    registers[pc] = 0;
  }

  ~State(){
    delete[] registers;
    delete [] stack;
  }
};
