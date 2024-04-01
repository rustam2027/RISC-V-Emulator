#include "../parser/Parser.hpp"
#include "../exceptions/RuntimeException.hpp"
#include "commands.hpp"
#include <string>
#include <vector>

void Add::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1] + state.registers[source2];
}

void Add::fill_args(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("add", args_amount, args.size()));
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}

void Addi::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source] + immediate;
}

void Addi::fill_args(vector<string> args) {
  // converted to types: Register, Register, int
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("addi", args_amount, args.size()));
  }
  dist = Parser::get_register(args[0]);
  source = Parser::get_register(args[1]);
  if (Parser::is_number(args[2])) {
      immediate = stoi(args[2]);
  } else {
    throw ParserException("invalid immediate in addi: " + args[2]);
  }
}

void And::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1] & state.registers[source2];
}

void And::fill_args(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("and", args_amount, args.size()));
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}

void Li::exec(State &state) {
  if (dist == zero) {
    return; // Может быть чтото посерьезнее
  }
  state.registers[dist] = immediate;
}

void Li::fill_args(vector<string> args) {
  // converted to types: Register, int
  int args_amount = 2;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("li", args_amount, args.size()));
  }
  dist = Parser::get_register(args[0]);
  if (Parser::is_number(args[1])) {
      immediate = stoi(args[1]);
  } else {
    throw ParserException("invalid immediate in li: " + args[1]);
  }
}

void Mv::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source];
}

void Mv::fill_args(vector<string> args) {
  // converted to types: Register, Register
  int args_amount = 2;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("mv", args_amount, args.size()));
  }
  dist = Parser::get_register(args[0]);
  source = Parser::get_register(args[1]);
}

void Or::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1] | state.registers[source2];
}

void Or::fill_args(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("or", args_amount, args.size()));
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}

void SLL::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1]
                          << (state.registers[source2] & ((1 << 5) - 1));
  // Performs logical left shift on the value in register rs1 by the shift
  // amount held in the lower 5 bits of register rs2.
}

void SLL::fill_args(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("sll", args_amount, args.size()));
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}

void SRL::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] =
      state.registers[source1] >> (state.registers[source2] & ((1 << 5) - 1));
  // Description: Logical right shift on the value in register rs1 by the shift
  // amount held in the lower 5 bits of register rs2
}

void SRL::fill_args(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("srl", args_amount, args.size()));
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}

void Sub::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1] - state.registers[source2];
}

void Sub::fill_args(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("sub", args_amount, args.size()));
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}

void Xor::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1] ^ state.registers[source2];
}

void Xor::fill_args(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("xor", args_amount, args.size()));
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}

void Ecall::exec(State &state) { 
  if (functions.count(state.registers[a7]) == 0) {
    throw EcallException("Wrong index of ecall " + std::to_string(state.registers[a7]));
  }
  functions[state.registers[a7]](state);
}

void Ecall::fill_args(vector<string> args) {
  // args amount: 0
  if (!args.empty()) {
    throw ParserException(Parser::exception_message("ecall", 0, args.size()));
  }
}

void Jump::exec(State &state) { state.registers[pc] = state.labels[label] - 1; }

void Jump::fill_args(vector<string> args) {
  int args_amount = 1;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("jump", args_amount, args.size()));
  }
  label = args[0];
}

void JumpAndLink::exec(State &state) {
  state.registers[return_register] = state.registers[pc]; // May be plus 1
  state.registers[pc] = state.labels[label] - 1;
}
 
void JumpAndLink::fill_args(vector<string> args) {
  int args_amount = 2;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("jump and link", args_amount, args.size()));
  }
  return_register = Parser::get_register(args[0]);
  label = args[1];
}

void BranchEqual::exec(State &state) {
  if (state.registers[first] == state.registers[second]) {
    state.registers[pc] = state.labels[label] - 1;
  }
}
 
void BranchEqual::fill_args(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("branch equal", args_amount, args.size()));
  }
  first = Parser::get_register(args[0]);
  second = Parser::get_register(args[1]);
  label = args[2];
}

void BranchNotEqual::exec(State &state) {
  if (state.registers[first] != state.registers[second]) {
    state.registers[pc] = state.labels[label] - 1;
  }
}
 
void BranchNotEqual::fill_args(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("branch not equal", args_amount, args.size()));
  }
  first = Parser::get_register(args[0]);
  second = Parser::get_register(args[1]);
  label = args[2];
}

void BranchLessThen::exec(State &state) {
  if (state.registers[first] < state.registers[second]) {
    state.registers[pc] = state.labels[label] - 1;
  }
}
 
void BranchLessThen::fill_args(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("branch less then", args_amount, args.size()));
  }
  first = Parser::get_register(args[0]);
  second = Parser::get_register(args[1]);
  label = args[2];
}

void BranchGreaterEqual::exec(State &state) {
  if (state.registers[first] >= state.registers[second]) {
    state.registers[pc] = state.labels[label] - 1;
  }
}
 
void BranchGreaterEqual::fill_args(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("branch greater equal", args_amount, args.size()));
  }
  first = Parser::get_register(args[0]);
  second = Parser::get_register(args[1]);
  label = args[2];
}


void Return::exec(State &state) { state.registers[pc] = state.registers[ra]; }

void Return::fill_args(vector<string> args) {
  int args_amount = 0;
  if (args.size() != args_amount) {
    throw ParserException(
        Parser::exception_message("return", args_amount, args.size()));
  }
}


void Sb::exec(State &state) {
  state.stack[dst + offset] = (std::byte) (state.registers[src] & 0xFF);
  //  SB instructions store 8-bit values from the low bits of register rs2 to memory.
}

void Sb::fill_args(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException(
      Parser::exception_message("store byte", args_amount, new_args.size()));
  }
  src = Parser::get_register(new_args[0]);
  dst = Parser::get_register(new_args[2]);
  offset = stoi(new_args[1]);
}
void Sh::exec(State & state) {
  state.stack[dst + offset + 1] = (std::byte) (state.registers[src] & 0xFF);
  state.stack[dst + offset] = (std::byte) ((state.registers[src] >> 8) & 0xFF);
  // The SH store 16-bit value from the low bits of register rs2 to memory.

}
void Sh::fill_args(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException(
      Parser::exception_message("store half-word", args_amount, new_args.size()));
  }
  src = Parser::get_register(new_args[0]);
  dst = Parser::get_register(new_args[2]);
  offset = stoi(new_args[1]);
}

void Sw::exec(State &state) {
  state.stack[dst + offset + 3] = (std::byte) (state.registers[src] & 0xFF);
  state.stack[dst + offset + 2] = (std::byte) ((state.registers[src] >> 8) & 0xFF);
  state.stack[dst + offset + 1] = (std::byte) ((state.registers[src] >> 16) & 0xFF);
  state.stack[dst + offset] = (std::byte) ((state.registers[src] >> 24) & 0xFF);
  // The SW, SH, and SB instructions store 32-bit, 16-bit, and 8-bit values from the low bits of register rs2 to memory.

}

void Sw::fill_args(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException(
      Parser::exception_message("store word", args_amount, new_args.size()));
  }
  src = Parser::get_register(new_args[0]);
  dst = Parser::get_register(new_args[2]);
  offset = stoi(new_args[1]);
}

void Lw::exec(State &state) {
  std::byte fourth = state.stack[src + offset];
  std::byte third = state.stack[src + offset - 1];
  std::byte second = state.stack[src + offset - 2];
  std::byte first = state.stack[src + offset - 3];
  state.registers[dst] = (int) ((first << 24) | (second << 16) | (third << 8) | fourth);
}

void Lw::fill_args(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException(
      Parser::exception_message("Load word", args_amount, new_args.size()));
  }
  dst = Parser::get_register(new_args[0]);
  src = Parser::get_register(new_args[2]);
  offset = stoi(new_args[1]);
}

void Lh::exec(State &state) {
  std::byte second = state.stack[src + offset];
  std::byte first = state.stack[src + offset - 1];
  state.registers[dst] = (int) ((first << 8) | (second));
}

void Lh::fill_args(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException(
      Parser::exception_message("Load half-word", args_amount, new_args.size()));
  }
  dst = Parser::get_register(new_args[0]);
  src = Parser::get_register(new_args[2]);
  offset = stoi(new_args[1]);
}

void Lb::exec(State &state) {
  std::byte first = state.stack[src + offset];
  state.registers[dst] = (int) (first);
}

void Lb::fill_args(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException(
      Parser::exception_message("Load byte", args_amount, new_args.size()));
  }
  dst = Parser::get_register(new_args[0]);
  src = Parser::get_register(new_args[2]);
  offset = stoi(new_args[1]);
}
