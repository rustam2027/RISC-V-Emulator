#include <cstddef>
#include <ios>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>

#include "../exceptions/RuntimeException.hpp"
#include "../frontend/Parser.hpp"
#include "BreakController.hpp"

void BreakController::open_interface() {
    int faild_requests = 0;
    while (true) {
        std::string request;
        std::cout << "> ";
        std::getline(std::cin, request);

        show_context();

        if (request == "continue" || request == "c") {
            break;
        } else if (request == "exit" || request == "q") {
            exit = true;
            break;
        } else if (request.rfind("show", 0) == 0 || request == "sr") {
            if (request.rfind("show stack", 0) == 0) {
                int from, to;
                std::string buffer;
                std::stringstream stream_request(request);
                stream_request >> buffer >> buffer >> from >> to;  // FIXME: Some how check that exactly two numbers were
                                                                   // given
                show_stack(from, to);
            } else if (request == "show registers" || request == "sr") {
                show_registers();
            } else {
                std::cout << "UNKNOWN COMMAND : '" << request << "'" << std::endl;
                faild_requests++;
            }
        } else if (request == "step in" || request == "s") {
            step_in();
            break;
        } else if (request == "next" || request == "n") {
            next();
            break;
        } else if (request == "help") {
            show_help();
        } else {
            std::cout << "UNKNOWN COMMAND : '" << request << "'" << std::endl;
            faild_requests++;
        }

        if (faild_requests >= 3) {
            show_help();
            faild_requests = 0;
        }
    }
}

void BreakController::show_stack(size_t from, size_t to) {
    std::cout << "SHOWING STACK" << std::endl;
    for (int i = from; i < to; i += 4) {
        std::cout << "[" << i << "]: ";
        long word = 0;
        for (int j = 0; j < 4; j++) {
            word *= 256;
            word += (int)global_state->stack[i + j];
        }
        std::cout << std::hex << word << std::endl;
    }
}

void BreakController::show_registers() {
    std::cout << "SHOWING REGISTERS" << std::endl;
    for (auto iter = Parser::registers_names.begin(); iter != Parser::registers_names.end(); ++iter) {
        std::cout << iter->first << ": " << std::hex << global_state->registers[iter->second] << std::endl;
    }
}

BreakController::BreakController(std::vector<Instruction *> instructions, std::map<std::string, int> labels) : exit(false) {
    instructions_ = instructions;
    global_state = new State(labels);
}

void BreakController::interpret() {
    while (global_state->registers[pc] < instructions_.size() * INSTRUCTION_SIZE) {
        if (global_state->registers[pc] % INSTRUCTION_SIZE != 0) {
            throw new RuntimeException("Wrong pc: " + std::to_string(global_state->registers[pc]));
        }

        if (dynamic_cast<EBreak *>(instructions_[global_state->registers[pc] /  // Check if
                                                                                // instruction is
                                                                                // instance EBReak
                                                 INSTRUCTION_SIZE]) != nullptr ||
            break_points[global_state->registers[pc] / INSTRUCTION_SIZE] == 1) {  // Or Break point is set
            open_interface();
        }

        instructions_[global_state->registers[pc] / INSTRUCTION_SIZE]->exec(*global_state);
        global_state->registers[pc] += INSTRUCTION_SIZE;

        if (exit) {
            return;
        }
    }
    // If the last command is a break point we can check condition after
    // execution
    if (dynamic_cast<EBreak *>(instructions_[global_state->registers[pc] / INSTRUCTION_SIZE - 1]) != nullptr ||
        break_points[global_state->registers[pc] / INSTRUCTION_SIZE - 1] == 1) {
        open_interface();
    }
}

void BreakController::show_context() {}

void BreakController::step_in() { break_points[(global_state->registers[pc] / INSTRUCTION_SIZE) + 1] = 1; }

void BreakController::next() {
    if ((instructions_.size() > (global_state->registers[pc] / INSTRUCTION_SIZE + 1)) &&
        dynamic_cast<JumpAndLink *>(instructions_[global_state->registers[pc] / INSTRUCTION_SIZE + 1]) != nullptr) {
        break_points[(global_state->registers[pc] / INSTRUCTION_SIZE) + 2] = 1;
    } else {
        step_in();
    }
}

void BreakController::show_help() {
    std::cout << "Oops look like u don't know what happening let me explain.\n"
              << "'help' -- to see this message\n"
              << "'continue' or 'c' to go to the next break point\n"
              << "'exit' or 'q' to exit debugger\n"
              << "'show stack n m' to view stack from n to m\n"
              << "'show registers' or 'sr' to view registers\n"
              << "'step in' to step inside\n"
              << "'next' or 'n' to not step inside\n";
}

BreakController::~BreakController() {
    for (Instruction *instruction : instructions_) {
        delete instruction;
    }
    delete global_state;
}
