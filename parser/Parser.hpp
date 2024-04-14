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

#include "../instructions/Instruction.hpp"
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

  map<string, function<Instruction *()>> func = {
      {"add", []() { return new Add(); }},
      {"addi", []() { return new Addi(); }},
      {"and", []() { return new And(); }},
      {"li", []() { return new Li(); }},
      {"mv", []() { return new Mv(); }},
      {"or", []() { return new Or(); }},
      {"sll", []() { return new SLL(); }},
      {"srl", []() { return new SRL(); }},
      {"sub", []() { return new Sub(); }},
      {"xor", []() { return new Xor(); }},
      {"ecall", []() { return new Ecall(); }},
      {"j", []() { return new Jump(); }},
      {"jal", []() { return new JumpAndLink(); }},
      {"beq", []() { return new BranchEqual(); }},
      {"bne", []() { return new BranchNotEqual(); }},
      {"blt", []() { return new BranchLessThen(); }},
      {"bge", []() { return new BranchGreaterEqual(); }},
      {"ret", []() { return new Return(); }}};

  string file;
  string concat(const string& sep, const vector<string>& strs);
  void string_replace(string& input, const string& src, const string& dst);
  void delete_commands(vector<Instruction *> commands);
  static vector<string> split(const string& s, char del, bool remove_comma);

public:
  Parser(string file);
  void preprocess();
  vector<Instruction *> get_commands();
  static Register get_register(const string &str);
  static vector<string> get_offset(const vector<string> &args);
  static bool is_number(const string &str);
  Instruction *get_command(const string &str);
  map<std::string, int> get_labels() { return labels; }

  static string exception_message(const string &command, int required,
                                  int provided) {
    return string("invalid amount of args in " + command + ": required " +
                  to_string(required) + ", provided " + to_string(provided));
  }
};
