#pragma once
#include "Command.h"
#include <map>
#include <functional>
#include "../consts.h"

using namespace std;
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

struct Ecall : Command {
  map<int, function<void(State&)>> functions = {
    {PRINT_INT, [](State& state) { printf("%d", state.registers[a0]); }},
    {READ_INT, [](State& state) { scanf("%d", &state.registers[a0]); }},
    {EXIT_0, [](State& state){ exit(0); }},
    {EXIT, [](State& state) { exit(state.registers[a0]); }},
    {PRINT_CHAR, [](State& state) { printf("%c", state.registers[a0]); }},
    {READ_CHAR, [](State& state) { scanf("%c", &state.registers[a0]); }},
    {SBRK, [](State& state) {}}, // ?
    {PRINT_STRING, [](State& state) { printf("%s", state.stack[state.registers[a0]]); }} // скорее всего полная хуйня

  };
  Ecall() {}

  void exec(State &state);
};