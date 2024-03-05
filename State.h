#pragma once
#include "consts.h"


struct State {
  int* registers;
  State(){
    registers = new int[AMOUNT_REGISTERS];
  }

  ~State(){
    delete registers;
  }
};
