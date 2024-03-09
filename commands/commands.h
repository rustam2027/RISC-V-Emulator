#pragma once
#include "Command.h"

struct Add : Command {
  Register dist;
  Register source1;
  Register source2;

  Add(Register dist, Register source1, Register source2): dist(dist), source1(source1), source2(source2) {}
  void exec(State &state);
};

struct Addi : Command {
  Register dist;
  Register source;
  int immediate;

  Addi(Register dist, Register source, int immediate): dist(dist), source(source), immediate(immediate) {}
  void exec(State &state);
};

struct And : Command {
  Register dist;
  Register source1;
  Register source2;

  And(Register dist, Register source1, Register source2): dist(dist), source1(source1), source2(source2) {}
  void exec(State &state);
};

struct Li : Command {
  Register dist;
  int immediate;

  Li(Register dist, int immediate): dist(dist), immediate(immediate) {}
  void exec(State& state);
};

struct Mv : Command {
  Register dist;
  Register source;

  Mv(Register dist, Register source): dist(dist), source(source) {}
  void exec(State& state);
};

struct Or : Command {
  Register dist;
  Register source1;
  Register source2;

  Or(Register dist, Register source1, Register source2): dist(dist), source1(source1), source2(source2) {}
  void exec(State &state);
};

struct SLL : Command {
  Register dist;
  Register source1;
  Register source2;

  SLL(Register dist, Register source1, Register source2): dist(dist), source1(source1), source2(source2) {}
  void exec(State &state);
};

struct SRL : Command {
  Register dist;
  Register source1;
  Register source2;

  SRL(Register dist, Register source1, Register source2): dist(dist), source1(source1), source2(source2) {}
  void exec(State &state);
};

struct Sub : Command {
  Register dist;
  Register source1;
  Register source2;

  Sub(Register dist, Register source1, Register source2): dist(dist), source1(source1), source2(source2) {}
  void exec(State &state);
};

struct Xor : Command {
  Register dist;
  Register source1;
  Register source2;

  Xor(Register dist, Register source1, Register source2): dist(dist), source1(source1), source2(source2) {}

  void exec(State &state);
};
