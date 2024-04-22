#include "BreakController.hpp"
#include "../exceptions/RuntimeException.hpp"
#include "../frontend/Parser.hpp"

#include <cstddef>
#include <ios>
#include <iostream>
#include <vector>

void BreakController::open_interface() {
  while (true) {
    std::string request;
    std::cout << "> ";
    std::getline(std::cin, request);

    if (request == "continue") {
      break;
    } else if (request == "exit") {
      exit = true;
      break;
    } else if (request.rfind("show", 0) == 0) {
      if (request == "show stack") {
        int from, to;
        std::cin >> from >> to;
        show_stack(from, to);
      } else if (request == "show registers") {
        show_registers();
      } else {
        std::cout << "UNKNOWN COMMAND" << std::endl;
      }
    } else {
      std::cout << "UNKNOWN COMMAND" << std::endl;
    }
  }

  global_state->debug_break = false;
}

void BreakController::show_stack(size_t from, size_t to) {
  std::cout << "SHOWING STACK" << std::endl;
}

void BreakController::show_registers() {
  std::cout << "SHOWING REGISTERS" << std::endl;
  for (auto iter=Parser::registers_names.begin(); iter!=Parser::registers_names.end(); ++iter) {
    std::cout << iter->first << ": " << std::hex << global_state->registers[iter->second] << std::endl;
  }

}

BreakController::BreakController(std::vector<Instruction *> instructions,
                                 std::map<std::string, int> labels): exit(false) {
  instructions_ = instructions;
  global_state = new State(labels);
}

void BreakController::interpret() {
  while (global_state->registers[pc] < instructions_.size() * 32) {
    if (global_state->registers[pc] % 32 != 0) {
      throw new RuntimeException("Wrong pc: " +
                                 std::to_string(global_state->registers[pc]));
    }
    instructions_[global_state->registers[pc] / 32]->exec(*global_state);
    global_state->registers[pc] += 32;
    if (global_state->debug_break) {
      open_interface();
    }
    if (exit) {
      break;
    }
  }
}

BreakController::~BreakController() {
  for (Instruction *instruction : instructions_) {
    delete instruction;
  }
  delete global_state;
}
