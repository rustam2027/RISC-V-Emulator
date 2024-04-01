#pragma once
#include "Command.hpp"
#include <map>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <string>
#include "../consts.hpp"

using namespace std;
struct Add : Command {
  Register dist, source1, source2;

  Add() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Addi : Command {
  Register dist, source;
  int immediate;

  Addi() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct And : Command {
  Register dist, source1, source2;

  And() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Li : Command {
  Register dist;
  int immediate;

  Li() {}
  void exec(State& state);
  void fill_args(vector<std::string> args);
};

struct Mv : Command {
  Register dist, source;

  Mv() {}
  void exec(State& state);
  void fill_args(vector<std::string> args);
};

struct Or : Command {
  Register dist, source1, source2;

  Or() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct SLL : Command {
  Register dist, source1, source2;

  SLL() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct SRL : Command {
  Register dist, source1, source2;

  SRL() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Sub : Command {
  Register dist, source1, source2;

  Sub() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Xor : Command {
  Register dist, source1, source2;

  Xor() {}
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Ecall : Command {
  map<int, function<void(State&)>> functions = {
    {PRINT_INT, [](State& state) { printf("%d", state.registers[a0]); }},
    {READ_INT, [](State& state) { scanf("%d", &state.registers[a0]); }},
    {EXIT_0, [](State& state){ exit(0); }},
    {EXIT, [](State& state) { exit(state.registers[a0]); }},
    {PRINT_CHAR, [](State& state) { printf("%c", state.registers[a0]); }},
    {READ_CHAR, [](State& state) { char c;
                                  scanf("%c", &c); 
                                  state.registers[a0] = (int) c; }}
  };
  Ecall() {}

  void exec(State &state);
  void fill_args(std::vector<std::string> args);
};

struct Jump : Command {
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct JumpAndLink : Command {
  Register return_register;
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct BranchEqual: Command {
  Register first;
  Register second;
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct BranchNotEqual: Command {
  Register first;
  Register second;
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct BranchLessThen: Command {
  Register first;
  Register second;
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct BranchGreaterEqual: Command {
  Register first;
  Register second;
  std::string label;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Return: Command {
  void exec(State &state);
  void fill_args(vector<std::string> args);
};
struct Sb : Command {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Sh : Command {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Sw : Command {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Lw : Command {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Lh : Command {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};

struct Lb : Command {
  Register src;
  Register dst;
  int offset;
  void exec(State &state);
  void fill_args(vector<std::string> args);
};
 
