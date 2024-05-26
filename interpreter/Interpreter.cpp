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

const int SHOW_REGISTER_CMD_LEN = 14;

int Interpreter::process_request(std::string request) {
    if (request == "") {
        return 0;
    }

    if (request == "continue" || request == "c") {
        stop = false;
        return 0;
    } else if (request == "exit" || request == "q") {
        exit = true;
        stop = false;
        return 0;
    } else if (request.rfind("show stack", 0) == 0) {
        std::string from, to;
        std::string buffer;
        std::stringstream stream_request(request);
        stream_request >> buffer >> buffer >> from >> to;  // FIXME: Some how check that exactly two numbers were
                                                           // given
        show_stack(Parser::get_immediate(from), Parser::get_immediate(to));
        return 0;
    } else if (request.rfind("show register", 0) == 0) {
        if (request == "show registers") {
            show_registers();
        } else if (request.size() > SHOW_REGISTER_CMD_LEN) {
            show_register(request.substr(SHOW_REGISTER_CMD_LEN));
        } else {
            std::cout << "UNKNOWN COMMAND : '" << request << "'" << std::endl;
            return 1;
        }
        return 0;
    } else if (request.rfind("sr", 0) == 0) {
        if (request.size() == 2) {
            show_registers();
        } else {
            show_register(request.substr(3));
        }
        return 0;
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
            return 1;
        }
        return 0;
    } else if (request == "step in" || request == "s") {
        step_in();
        stop = false;
        return 0;
    } else if (request == "step over" || request == "n") {
        step_over();
        stop = false;
        return 0;
    } else if (request == "step out" || request == "o") {
        step_out();
        stop = false;
        return 0;
    } else if (request == "help") {
        show_help();
        return 0;
    } else if (request.rfind("breakpoint set --name", 0) == 0) {
        breakpoint_set_by_label(request.substr(22));
        return 0;
    } else if (request.rfind("breakpoint set --line", 0) == 0) {
        breakpoint_set_by_number(Parser::get_immediate(request.substr(22)));
        return 0;
    } else {
        std::cout << "UNKNOWN COMMAND : '" << request << "'" << std::endl;
        return 1;
    }

}

void Interpreter::open_interface() {
    if (!debug) {
        return;
    }
    stop = true;
    show_context();
    int failed_requests = 0;
    while (stop) {
        std::string request;
        std::cout << "> ";
        std::getline(std::cin, request);
        if (request == "") {
            continue;
        }
        if (process_request(request) == 0) {
            ++failed_requests;
        }
        if (failed_requests >= 3) {
            show_help();
            failed_requests = 0;
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
    : exit(false), instructions_(instructions), global_state(new State(labels)), debug(debug_flag), all_lines_in(all_lines), from_in_to_inparse(in_to_inparse), from_inparse_to_in(inparse_to_in) {
}

bool Interpreter::has_lines() {
    return global_state->registers[pc] < instructions_.size() * INSTRUCTION_SIZE && !exit;
}

void Interpreter::interpret() {
    bool first = true;

    if (first_instruction) {
        first = false;
        first_instruction = false;
    }

    while(has_lines()) {
        if (global_state->registers[pc] % INSTRUCTION_SIZE != 0) {
            throw new RuntimeException("Wrong pc: " + std::to_string(global_state->registers[pc]));
        }

        size_t index = global_state->registers[pc] / INSTRUCTION_SIZE;

        if (!first && debug && ((dynamic_cast<EBreak *>(instructions_[index]) != nullptr || break_points[index] == 1) || break_on_next)) { 
            break_on_next = false;
            stop = true;
            if (!set_manually[index]) {
                break_points[index] = 0;
            }
            return;
        }
        

        instructions_[global_state->registers[pc] / INSTRUCTION_SIZE]->exec(*global_state);
        global_state->registers[pc] += INSTRUCTION_SIZE;
        first = false;

        if (exit) {
            return;
        }
    }

    if (debug && (break_points[global_state->registers[pc] / INSTRUCTION_SIZE - 1] == 1 || break_on_next)) {
        stop = true;
        return;
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

void Interpreter::breakpoint_set_by_label(std::string label) {
    if (global_state->labels.find(label) != global_state->labels.cend()) {
        break_points[global_state->labels[label]] = 1;
        set_manually[global_state->labels[label]] = 1;
    } else {
        std::cout << "UNKNOWN LABEL: " << label << std::endl;
    }
}

void Interpreter::breakpoint_set_by_number(int num) {
    if (all_lines_in.size() > num) {
        while (from_in_to_inparse[num] == -1) {num--;}
        break_points[from_in_to_inparse[num]] = 1;
        set_manually[from_in_to_inparse[num]] = 1;
    } else {
        std::cout << "NUMBER IS TOO BIG: "<< num << std::endl;
    }
}

void Interpreter::step_over() {
    size_t index = global_state->registers[pc] / INSTRUCTION_SIZE;

    if (index < instructions_.size() && dynamic_cast<JumpAndLink *>(instructions_[index]) != nullptr) {
        break_points[index + 1] = 1;
        return;
    } else {
        break_on_next = true;
    }
}

void Interpreter::step_in() {
    break_on_next = true;
}

void Interpreter::step_out() {
    break_points[(global_state->registers[ra] / INSTRUCTION_SIZE) + 1] = 1;
}

void Interpreter::show_help() {
    std::cout << "Oops look like u don't know what happening let me explain." << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "- continue (c): Continue execution until the next breakpoint or the end of the program." << std::endl;
    std::cout << "- exit (q): Exit the debugger." << std::endl;
    std::cout << "- show stack <from> <to>: Show the stack contents from address <from> to <to>." << std::endl;
    std::cout << "- show registers (sr): Show the contents of all registers." << std::endl;
    std::cout << "- show register <name>: Show the contents of the specified register." << std::endl;
    std::cout << "- step in (s): Execute the next instruction and step into any function calls." << std::endl;
    std::cout << "- step over (n): Execute the next instruction and skip over any function calls." << std::endl;
    std::cout << "- step out (o): Execute until the current function returns." << std::endl;
    std::cout << "- help: Show this help message." << std::endl;
}

bool Interpreter::is_breakpoint(size_t num) {
    if (from_in_to_inparse[num] >= 0) {
        return break_points[from_in_to_inparse[num]] & set_manually[from_in_to_inparse[num]];
    }
    return false;
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

int Interpreter::get_line() {
    int index = global_state->registers[pc] / INSTRUCTION_SIZE;
    if (index >= from_inparse_to_in.size()) {
        return -1;
    }
    return from_inparse_to_in[index];
}

void Interpreter::make_step(std::string command) {

}

bool Interpreter::has_lines() {

}
