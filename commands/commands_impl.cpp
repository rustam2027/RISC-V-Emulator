#include "commands.h"

void Add::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] + state.registers[source2];
}

void Addi::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source] + immediate;
}

void And::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] & state.registers[source2];
}

void Li::exec(State& state) {
    if (dist == zero) {
      return;  // Может быть чтото посерьезнее
    }
    state.registers[dist] = immediate;
}

void Mv::exec(State& state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source];
}

void Or::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] | state.registers[source2];
}

void SLL::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] << (state.registers[source2] & ((1 << 5) - 1));
    // Performs logical left shift on the value in register rs1 by the shift amount held in the lower 5 bits of register rs2.
}

void SRL::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] >> (state.registers[source2] & ((1 << 5) - 1));
    // Description: Logical right shift on the value in register rs1 by the shift amount held in the lower 5 bits of register rs2
}

void Sub::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] - state.registers[source2];
}

void Xor::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] ^ state.registers[source2];
}
void Ecall::exec(State &state) {
  functions[state.registers[a7]](state);
}