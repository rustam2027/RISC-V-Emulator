#include <algorithm>
#include <cstddef>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../exceptions/RuntimeException.hpp"
#include "../frontend/Parser.hpp"
#include "Interpreter.hpp"

void Interpreter::open_interface() {
    int faild_requests = 0;

    show_context();
    while (true) {
        std::string request;
        std::cout << "> ";
        std::getline(std::cin, request);
        if (request == "") {
            continue;
        }

        if (request == "continue" || request == "c") {
            break;
        } else if (request == "exit" || request == "q") {
            exit = true;
            break;
        } else if (request.rfind("show stack", 0) == 0) {
            int from, to;
            std::string buffer;
            std::stringstream stream_request(request);
            stream_request >> buffer >> buffer >> from >> to;  // FIXME: Some how check that exactly two numbers were
                                                               // given
            show_stack(from, to);
        } else if (request.rfind("show register", 0) == 0) {
            if (request == "show registers") {
                show_registers();
            } else if (request.size() > 14) {  // Size of "show registers"
                show_register(request.substr(14));
            } else {
                std::cout << "UNKNOWN COMMAND : '" << request << "'" << std::endl;
            }
        } else if (request.rfind("sr", 0) == 0) {
            if (request.size() == 2) {
                show_registers();
            } else {
                show_register(request.substr(3));
            }
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

void Interpreter::show_stack(size_t from, size_t to) {
    std::cout << "SHOWING STACK" << std::endl;
    for (int i = from; i < to; i++) {
        std::cout << "[" << i * 8 << "]: ";
        long word = 0;
        for (int j = 0; j < 8; j++) {
            word = word << 8;
            word += (int)global_state->stack[i * 8 + j];
        }
        std::cout << get_hex(word) << std::endl;
    }
}

void Interpreter::show_registers() {
    std::cout << "SHOWING REGISTERS" << std::endl;
    for (auto iter = Parser::registers_names.begin(); iter != Parser::registers_names.end(); ++iter) {
        std::cout << iter->first << ": " << get_hex(global_state->registers[iter->second]) << std::endl;
    }
}

void Interpreter::show_register(std::string rg_str) {
    try {
        Register rg_reg = Parser::get_register(rg_str);
        std::cout << '[' << rg_str << "]: " << get_hex(global_state->registers[rg_reg]) << std::endl;
    } catch (const ParserException& pe) {
        std::cout << pe.get_message() << std::endl;
    }
}

Interpreter::Interpreter(std::vector<Instruction *>& instructions, std::map<std::string, int>& labels, std::vector<std::string>& all_lines,
                                 std::vector<int>& in_to_inparse, std::vector<int>& inparse_to_in, bool debug_flag)
    : exit(false) {
    instructions_ = instructions;
    global_state = new State(labels);
    debug = debug_flag;

    all_lines_in = all_lines;

    from_in_to_inparse = in_to_inparse;
    from_inparse_to_in = inparse_to_in;
}

void Interpreter::interpret() {
    while (global_state->registers[pc] < instructions_.size() * INSTRUCTION_SIZE) {
        if (global_state->registers[pc] % INSTRUCTION_SIZE != 0) {
            throw new RuntimeException("Wrong pc: " + std::to_string(global_state->registers[pc]));
        }

        if (debug && (dynamic_cast<EBreak *>(instructions_[global_state->registers[pc] /  // Check if
                                                                                // instruction is
                                                                                // instance EBReak
                                                 INSTRUCTION_SIZE]) != nullptr ||
            break_points[global_state->registers[pc] / INSTRUCTION_SIZE] == 1)) {  // Or Break point is set
            open_interface();
            break_points[global_state->registers[pc] / INSTRUCTION_SIZE] = 0;
        }

        instructions_[global_state->registers[pc] / INSTRUCTION_SIZE]->exec(*global_state);
        global_state->registers[pc] += INSTRUCTION_SIZE;

        if (exit) {
            return;
        }
    }
    // If the last command is a break point we can check condition after
    // execution
    if (debug && break_points[global_state->registers[pc] / INSTRUCTION_SIZE - 1] == 1) {
        open_interface();
    }
}

void Interpreter::show_context() {
    int index = global_state->registers[pc] / INSTRUCTION_SIZE;
     
    size_t min_index = from_inparse_to_in[std::max(0, ((int)index) - 2)];
    size_t max_index = from_inparse_to_in[std::min((int)instructions_.size() - 1, index + 2)];

    if (min_index > max_index) {
        min_index = std::max(0, from_inparse_to_in[index] - 2);
        max_index = std::min(from_inparse_to_in[index] + 2, (int) from_in_to_inparse.size());
    }
    std::cout << std::endl;

    for (size_t i = min_index; i <= max_index; i++) {
        if (index < from_inparse_to_in.size() && i == from_inparse_to_in[index]) {
            std::cout << " --> ";
        } else {
            std::cout << "     ";
        }
        std::string num = to_string(i);
        num.resize(3, ' ');

        std::cout << num << "|" << all_lines_in[i] << std::endl;
    }
}

void Interpreter::step_in() {
    if ((instructions_.size() > ((global_state->registers[pc] / INSTRUCTION_SIZE)))) {
        if (dynamic_cast<JumpAndLink *>(instructions_[(global_state->registers[pc] / INSTRUCTION_SIZE)]) != nullptr) {
            JumpAndLink *jal = dynamic_cast<JumpAndLink *>(instructions_[(global_state->registers[pc] / INSTRUCTION_SIZE)]);
            break_points[global_state->labels[jal->label]] = 1;
            return;
        } else if (dynamic_cast<Return *>(instructions_[(global_state->registers[pc] / INSTRUCTION_SIZE)]) != nullptr) {
            break_points[global_state->registers[ra] / INSTRUCTION_SIZE + 1] = 1;
            return;
        } else if (dynamic_cast<Jump *>(instructions_[(global_state->registers[pc] / INSTRUCTION_SIZE)]) != nullptr) {
            Jump *j = dynamic_cast<Jump *>(instructions_[(global_state->registers[pc] / INSTRUCTION_SIZE)]);
            break_points[global_state->labels[j->label]] = 1;
            return;
        }
    }
    break_points[(global_state->registers[pc] / INSTRUCTION_SIZE) + 1] = 1;
}

void Interpreter::next() {
    break_points[(global_state->registers[pc] / INSTRUCTION_SIZE) + 1] = 1;
}

void Interpreter::show_help() {
    std::cout << "Oops look like u don't know what happening let me explain.\n"
              << "'help' -- to see this message\n"
              << "'continue' or 'c' to go to the next break point\n"
              << "'exit' or 'q' to exit debugger\n"
              << "'show stack n m' to view stack from n to m\n"
              << "'show registers' or 'sr' to view registers\n"
              << "'show register rg' or 'sr rg' to view only rg register" << "'step in' to step inside\n"
              << "'next' or 'n' to not step inside\n";
}

Interpreter::~Interpreter() {
    for (Instruction *instruction : instructions_) {
        delete instruction;
    }
    delete global_state;
}

std::string Interpreter::get_hex(long num) {
    std::string str;
    std::string nul;

    std::stringstream ss;
    ss << std::hex << num;

    str = ss.str();

    for (int i = 0; i < 16 - str.size(); i++) {
        nul.push_back('0');
    }
    transform(str.begin(), str.end(), str.begin(), ::toupper);

    return "0x" + nul + str;
}
