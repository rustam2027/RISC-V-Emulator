#include "commands.hpp"
#include "../parser/Parser.hpp"

//TODO: convert 77 to normal exception

void Add::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] + state.registers[source2];
}

void Add::fill_args(vector<string> args) {
  // args amount: 3
  // converted to types: Register, Register, Register 
  if (args.size() != 3) {
    throw 77;
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
  // args amount: 3
  // converted to types: Register, Register, int 
  if (args.size() != 3) {
    throw 77;
  }
  dist = Parser::get_register(args[0]);
  source = Parser::get_register(args[1]);
  immediate = stoi(args[2]);
}

void And::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] & state.registers[source2];
}

void And::fill_args(vector<string> args) {
  // args amount: 3
  // converted to types: Register, Register, Register 
  if (args.size() != 3) {
    throw 77;
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}

void Li::exec(State& state) {
    if (dist == zero) {
      return;  // Может быть чтото посерьезнее
    }
    state.registers[dist] = immediate;
}

void Li::fill_args(vector<string> args) {
  // args amount: 2
  // converted to types: Register, int 
  if (args.size() != 2) {
    throw 77;
  }
  dist = Parser::get_register(args[0]);
  immediate = stoi(args[1]);
}

void Mv::exec(State& state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source];
}

void Mv::fill_args(vector<string> args) {
  // args amount: 2
  // converted to types: Register, Register
  if (args.size() != 2) {
    throw 77;
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
  // args amount: 3
  // converted to types: Register, Register, Register 
  if (args.size() != 3) {
    throw 77;
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}

void SLL::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] << (state.registers[source2] & ((1 << 5) - 1));
    // Performs logical left shift on the value in register rs1 by the shift amount held in the lower 5 bits of register rs2.
}

void SLL::fill_args(vector<string> args) {
  // args amount: 3
  // converted to types: Register, Register, Register 
  if (args.size() != 3) {
    throw 77;
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}

void SRL::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] >> (state.registers[source2] & ((1 << 5) - 1));
    // Description: Logical right shift on the value in register rs1 by the shift amount held in the lower 5 bits of register rs2
}

void SRL::fill_args(vector<string> args) {
  // args amount: 3
  // converted to types: Register, Register, Register 
  if (args.size() != 3) {
    throw 77;
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
  // args amount: 3
  // converted to types: Register, Register, Register 
  if (args.size() != 3) {
    throw 77;
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
  // args amount: 3
  // converted to types: Register, Register, Register 
  if (args.size() != 3) {
    throw 77;
  }
  dist = Parser::get_register(args[0]);
  source1 = Parser::get_register(args[1]);
  source2 = Parser::get_register(args[1]);
}


// void Ecall::exec(State &state) {
//   functions[state.registers[a7]](state);
// }
