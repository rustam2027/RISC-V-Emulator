#pragma once
#include "Instruction.hpp"
#include <map>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <string>
#include "../consts.hpp"

using namespace std;
struct Add : Instruction {
  Register dist, source1, source2;

  Add() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Addi : Instruction {
  Register dist, source;
  int immediate;

  Addi() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct And : Instruction {
  Register dist, source1, source2;

  And() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Li : Instruction {
  Register dist;
  int immediate;

  Li() {}
  void exec(State& state);
  void fill_args(vector<std::string> args);
};

struct Mv : Instruction {
  Register dist, source;

  Mv() {}
  void exec(State& state);
  void fill_args(vector<std::string> args);
};

struct Or : Instruction {
  Register dist, source1, source2;

  Or() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct SLL : Instruction {
  Register dist, source1, source2;

  SLL() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct SRL : Instruction {
  Register dist, source1, source2;

  SRL() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Sub : Instruction {
  Register dist, source1, source2;

  Sub() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Xor : Instruction {
  Register dist, source1, source2;

  Xor() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Ecall : Instruction {
  map<int, function<void(State&)>> functions = {
    {PRINT_INT, [](State& state) { printf("%ld", state.registers[a0]); }},
    {READ_INT, [](State& state) { scanf("%ld", &state.registers[a0]); }},
    {EXIT_0, [](State& state){ exit(0); }},
    {EXIT, [](State& state) { exit(state.registers[a0]); }},
    {PRINT_CHAR, [](State& state) { printf("%c", (char) state.registers[a0]); }},
    {READ_CHAR, [](State& state) { char c;
                                  scanf("%c", &c); 
                                  state.registers[a0] = (long) c; }}
  };
  Ecall() {}

  void exec(State &state);
  void fill_args(std::vector<std::string> args);
};

struct Jump : Instruction {
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct JumpAndLink : Instruction {
  Register return_register;
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct BranchEqual: Instruction {
  Register first;
  Register second;
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct BranchNotEqual: Instruction {
  Register first;
  Register second;
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct BranchLessThen: Instruction {
  Register first;
  Register second;
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct BranchGreaterEqual: Instruction {
  Register first;
  Register second;
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Return: Instruction {
  void exec(State &state);
  void fill_args(vector<std::string> args);
};
struct Sb : Instruction {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Sh : Instruction {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Sw : Instruction {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Lw : Instruction {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Lh : Instruction {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Lb : Instruction {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};
 
