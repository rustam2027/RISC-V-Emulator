#include "Interpreter.hpp"
#include "../exceptions/RuntimeException.hpp"
#include <algorithm>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Interpreter::Interpreter(std::vector<Instruction *> instructions,
                         std::map<std::string, int> labels) {
  this->instructions = instructions;
  global_state = new State(labels);
}

void Interpreter::interpret() {
  while (global_state->registers[pc] < instructions.size() * 32) {
    if (global_state->registers[pc] % 32 != 0) {
      throw new RuntimeException("Wrong pc: " + to_string(global_state->registers[pc]));
    }
    instructions[global_state->registers[pc] / 32]->exec(*global_state);
    global_state->registers[pc] += 32;
  }
}

Interpreter::~Interpreter() {
  for (Instruction *instruction : instructions) {
    delete instruction;
  }
  delete global_state;
}
