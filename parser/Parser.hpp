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
  void delete_instructions(vector<Instruction *> instructions);
  static vector<string> split(const string& s, char del, bool remove_comma);

  static bool is_binary_number(const string& str);
  static bool is_hex_number(const string& str);
  static bool is_dec_number(const string& str);

  static int get_immediate(const string &str);
  static int is_binary_char(char c);
  static bool is_hex_char(char c);

public:
  Parser(string file);
  void preprocess();
  vector<Instruction *> get_instructions();
  static Register get_register(const string &str);
  static vector<string> get_offset(const vector<string> &args);
  static bool is_number(const string &str);
  Instruction *get_instruction(const string &str);
  map<std::string, int> get_labels() { return labels; }

  static string exception_message(const string &instruction, int required,
                                  int provided) {
    return string("invalid amount of args in " + instruction + ": required " +
                  to_string(required) + ", provided " + to_string(provided));
  }
};
