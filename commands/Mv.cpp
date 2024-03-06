#include "Command.h"
#include "../Register.h"


struct Mv: public Command {
  Register dist;
  Register source;

  Mv(Register dist, Register source): dist(dist), source(source) {}

  void exec(State& state) {
    state.registers[dist] = state.registers[source];
  }
};
