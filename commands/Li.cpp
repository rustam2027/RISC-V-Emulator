#include "Command.h"
#include "../Register.h"


struct Li: public Command {
  Register dist;
  int immediate;

  Li(Register dist, int immediate): dist(dist), immediate(immediate) {}
  
  void exec(State& state) {
    if (dist == zero) {
      return;  // Может быть чтото посерьезнее
    }
    state.registers[dist] = immediate;
  }
};
