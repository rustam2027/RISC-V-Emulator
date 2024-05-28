#pragma once

#include <map>
#include <string>
#include "Register.hpp"
#include "consts.hpp"
#include <vector>

struct State {
  std::vector<long> registers;
  std::byte *memory;
  std::map<std::string, int> labels;

  State() {
    registers = std::vector<long>(AMOUNT_REGISTERS);
    memory = new std::byte[AMOUNT_STACK];
    registers[zero] = 0;
    registers[pc] = 0;
  };

  State(std::map<std::string, int> labels) {
    registers = std::vector<long>(AMOUNT_REGISTERS);
    memory = new std::byte[AMOUNT_STACK];
    registers[zero] = 0;
    registers[pc] = 0;
    this->labels = labels;
  }

  ~State() {
    delete[] memory;
  }
};
