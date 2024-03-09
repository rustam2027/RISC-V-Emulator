#include "commands.h"

void Add::exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] + state.registers[source2];
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