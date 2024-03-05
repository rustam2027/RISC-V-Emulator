#include "Command.h"
#include "../Register.h"


struct Li: virtual Command {
  Register dist;
  int immediate;

  Li(Register dist, int immediate): dist(dist), immediate(immediate) {}
  
  void exec(State& state) {
    state.registers[dist] = immediate;
  }
};
