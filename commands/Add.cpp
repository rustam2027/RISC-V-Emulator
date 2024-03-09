#include "../Register.h"
#include "Command.h"

struct Add : public Command {
  Register dist;
  Register source1;
  Register source2;

  Add(Register dist, Register source1, Register source2): dist(dist), source1(source1), source2(source2) {}

  void exec(State &state) {
    if (dist == zero) {
      return;
    }
    state.registers[dist] = state.registers[source1] + state.registers[source2];
  }
};
