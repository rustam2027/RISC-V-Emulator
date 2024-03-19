#pragma once

#include <map>
#include <string>

#include "Register.hpp"
#include "consts.hpp"

struct State {
  int *registers;
  int *stack;
  std::map<std::string, int> labels;

  State() = default;

  State(std::map<std::string, int> labels) {
    registers = new int[AMOUNT_REGISTERS];
    stack = new int[AMOUNT_STACK];
    registers[zero] = 0;
    registers[pc] = 0;
    this->labels = labels;
  }

  ~State() {
    delete[] registers;
    delete[] stack;
  }
};
