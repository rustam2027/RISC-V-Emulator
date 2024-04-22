#include "BreakController.hpp"
#include "../exceptions/RuntimeException.hpp"

#include <cstddef>
#include <iostream>
#include <vector>

void BreakController::open_interface() {
  while (true) {
    std::string request;
    std::cout << "> ";
    std::getline(std::cin, request);

    if (request == "continue") {
      break;
    } else if (request.rfind("show", 0) == 0) {
      if (request == "show stack") {
        int from, to;
        std::cin >> from >> to;
        show_stack(from, to);
      } else if (request == "show registers") {
        show_registers();
      } else {
        std::cout << "Неизвестная команда" << std::endl;
      }
    } else {
      std::cout << "Неизвестная команда" << std::endl;
    }
  }
}

void BreakController::show_stack(size_t from, size_t to) {
  std::cout << "SHOWING STACK" << std::endl;
}

void BreakController::show_registers() {
  std::cout << "SHOWING REGISTERS" << std::endl;
}


BreakController::BreakController(std::vector<Instruction *> instructions,
                                 std::map<std::string, int> labels) {
  instructions = instructions;
  global_state = new State(labels);
}

void BreakController::interpret() {
  while (global_state->registers[pc] < instructions.size() * 32) {
    if (global_state->registers[pc] % 32 != 0) {
      throw new RuntimeException("Wrong pc: " +
                                 std::to_string(global_state->registers[pc]));
    }
    if (global_state->debug_break) {
      open_interface();
    }
    instructions[global_state->registers[pc] / 32]->exec(*global_state);
    global_state->registers[pc] += 32;
  }
}

BreakController::~BreakController() {
  for (Instruction *instruction : instructions) {
    delete instruction;
  }
  delete global_state;
}
