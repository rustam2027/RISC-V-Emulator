#include "Command.h"

struct Add : public Command {
  Register dist;
  Register source1;
  Register source2;

  Add(Register dist, Register source1, Register source2): dist(dist), source1(source1), source2(source2) {}
  void exec(State &state);
};

struct Li: public Command {
  Register dist;
  int immediate;

  Li(Register dist, int immediate): dist(dist), immediate(immediate) {}
  void exec(State& state);
};

struct Mv: public Command {
  Register dist;
  Register source;

  Mv(Register dist, Register source): dist(dist), source(source) {}
  void exec(State& state);
};