#include "../Register.h"
#include "Command.h"

class Add : virtual Command {
  Register dist;
  Register source1;
  Register source2;

  Add(Register dist, Register source1, Register source2): dist(dist), source1(source1), source2(source2) {}

  void exec(State &state) {
    state.registers[dist] = state.registers[source1] + state.registers[source2];
  }
};
