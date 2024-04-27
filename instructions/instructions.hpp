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

  Add(vector<std::string> args);
  void exec(State &state);
};

struct Li : Instruction {
  Register dist;
  int immediate;

  Li(vector<std::string> args);
  void exec(State& state);
};

struct Addi : Instruction {
  Register dist, source;
  int immediate;

  Addi(vector<std::string> args);
  void exec(State &state);
};

struct And : Instruction {
  Register dist, source1, source2;

  And(vector<std::string> args);
  void exec(State &state);
};

struct Mv : Instruction {
  Register dist, source;

  Mv(vector<std::string> args);
  void exec(State& state);
};

struct Or : Instruction {
  Register dist, source1, source2;

  Or(vector<std::string> args);
  void exec(State &state);
};

struct SLL : Instruction {
  Register dist, source1, source2;

  SLL(vector<std::string> args);
  void exec(State &state);
};
struct SLLI : Instruction {
  Register dist, source;
  long immediate;

  SLLI(vector<std::string> args);
  void exec(State &state);
};
struct SRL : Instruction {
  Register dist, source1, source2;

  SRL(vector<std::string> args);
  void exec(State &state);
};
struct SRLI : Instruction {
  Register dist, source;
  long immediate;

  SRLI(vector<std::string> args);
  void exec(State &state);
};

struct Sub : Instruction {
  Register dist, source1, source2;

  Sub(vector<std::string> args);
  void exec(State &state);
};

struct Xor : Instruction {
  Register dist, source1, source2;

  Xor(vector<std::string> args);
  void exec(State &state);
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
  Ecall(std::vector<std::string> args);
  void exec(State &state);
};

struct Jump : Instruction {
  std::string label;
  Jump(vector<std::string> args);
  void exec(State &state);
};

struct JumpAndLink : Instruction {
  Register return_register;
  std::string label;

  JumpAndLink(vector<std::string> args);
  void exec(State &state);
};

struct BranchEqual: Instruction {
  Register first, second;
  std::string label;

  BranchEqual(vector<std::string> args);
  void exec(State &state);
};

struct BranchEqualZero : Instruction {
  Register first;
  std::string label;

  BranchEqualZero(vector<std::string> args);
  void exec(State &state);
};

struct BranchNotEqual: Instruction {
  Register first, second;
  std::string label;

  BranchNotEqual(vector<std::string> args);
  void exec(State &state);
};

struct BranchLessThen: Instruction {
  Register first, second;
  std::string label;

  BranchLessThen(vector<std::string> args);
  void exec(State &state);
};

struct BranchGreaterEqual: Instruction {
  Register first, second;
  std::string label;

  BranchGreaterEqual(vector<std::string> args);
  void exec(State &state);
};

struct BranchGreaterThen: Instruction {
  Register first, second;
  std::string label;

  BranchGreaterThen(vector<std::string> args);
  void exec(State &state);
};

struct Return: Instruction {
  Return(vector<std::string> args);
  void exec(State &state);
};


struct Sb : Instruction {
  Register src, dst;
  int offset;

  Sb(vector<std::string> args);
  void exec(State &state);
};

struct Sh : Instruction {
  Register src, dst;
  int offset;

  Sh(vector<std::string> args);
  void exec(State &state);
};

struct Sw : Instruction {
  Register src, dst;
  int offset;

  Sw(vector<std::string> args);
  void exec(State &state);
};

struct Lw : Instruction {
  Register src, dst;
  int offset;

  Lw(vector<std::string> args);
  void exec(State &state);
};

struct Lh : Instruction {
  Register src, dst;
  int offset;

  Lh(vector<std::string> args);
  void exec(State &state);
};

struct Lb : Instruction {
  Register src, dst;
  int offset;

  Lb(vector<std::string> args);
  void exec(State &state);
};

struct EBreak : Instruction {
  EBreak(vector<std::string> args);
  void exec(State &state);
};

