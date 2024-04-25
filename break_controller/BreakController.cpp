#include "BreakController.hpp"
#include "../exceptions/RuntimeException.hpp"
#include "../frontend/Parser.hpp"

#include <cstddef>
#include <ios>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

void BreakController::open_interface() {
  while (true) {
    std::string request;
    std::cout << "> ";
    std::getline(std::cin, request);

    if (request == "continue") {
      break;
    } else if (request == "exit" || request == "q") {
      exit = true;
      break;
    } else if (request.rfind("show", 0) == 0) {
      if (request.rfind("show stack", 0) == 0) {
        int from, to;
        std::string buffer;
        std::stringstream stream_request(request);
        stream_request >> buffer >> buffer >> from >> to;  # FIXME: Some how check that exactly two numbers were given
        show_stack(from, to);
      } else if (request == "show registers") {
        show_registers();
      } else {
        std::cout << "UNKNOWN COMMAND : '" << request << "'" << std::endl;
      }
    } else {
      std::cout << "UNKNOWN COMMAND : '" << request << "'" << std::endl;
    }
  }

  global_state->debug_break = false;
}

void BreakController::show_stack(size_t from, size_t to) {
  std::cout << "SHOWING STACK" << std::endl;
  for (int i = from; i < to; i += 4) {
    std::cout << "[" << i << "]: ";
    long word = 0;
    for (int j = 0; j < 4; j++) {
      word *= 256;
      word += (int) global_state->stack[i + j];
    }
    std::cout << std::hex << word << std::endl;
  }
}

void BreakController::show_registers() {
  std::cout << "SHOWING REGISTERS" << std::endl;
  for (auto iter = Parser::registers_names.begin();
       iter != Parser::registers_names.end(); ++iter) {
    std::cout << iter->first << ": " << std::hex
              << global_state->registers[iter->second] << std::endl;
  }
}

BreakController::BreakController(std::vector<Instruction *> instructions,
                                 std::map<std::string, int> labels)
    : exit(false) {
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
