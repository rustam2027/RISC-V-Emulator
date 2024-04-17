#pragma once
#include <cassert>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "../instructions/instructions.hpp"
#include "../exceptions/ParserException.hpp"

using namespace std;

class Parser {
private:
  struct Macro {
    vector<string> params;
    vector<string> macro_lines;
  };
  static map<string, Register> registers_names;
  map<string, int> labels;
  map<string, Macro> macro;

  map<string, function<Instruction* (vector<string> args)>> func = {
      {"add", [](vector<string> args) { return new Add(args); }},
      {"li", [](vector<string> args) { return new Li(args); }},
      {"addi", [](vector<string> args) { return new Addi(args); }},
      {"and", [](vector<string> args) { return new And(args); }},
      {"mv", [](vector<string> args) { return new Mv(args); }},
      {"or", [](vector<string> args) { return new Or(args); }},
      {"sll", [](vector<string> args) { return new SLL(args); }},
      {"srl", [](vector<string> args) { return new SRL(args); }},
      {"sub", [](vector<string> args) { return new Sub(args); }},
      {"xor", [](vector<string> args) { return new Xor(args); }},
      {"ecall", [](vector<string> args) { return new Ecall(args); }},
      {"j", [](vector<string> args) { return new Jump(args); }},
      {"jal", [](vector<string> args) { return new JumpAndLink(args); }},
      {"beq", [](vector<string> args) { return new BranchEqual(args); }},
      {"bne", [](vector<string> args) { return new BranchNotEqual(args); }},
      {"blt", [](vector<string> args) { return new BranchLessThen(args); }},
      {"bge", [](vector<string> args) { return new BranchGreaterEqual(args); }},
      {"ret", [](vector<string> args) { return new Return(args); }}
      };

  string file;
  string concat(const string& sep, const vector<string>& strs);
  static vector<string> split(const string& s, char del, bool remove_comma);
  void string_replace(string& input, const string& src, const string& dst);

  void delete_instructions(vector<Instruction *> instructions);
  Instruction* get_instruction(const string &str, vector<string> args);

public:
  Parser(string file);
  void preprocess();
  vector<Instruction*> get_instructions();
  static Register get_register(const string &str);
  static vector<string> get_offset(const vector<string> &args);
  static bool is_number(const string &str);
  map<std::string, int> get_labels() { return labels; }
};
