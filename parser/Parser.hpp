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

#include "../commands/Command.hpp"
#include "../commands/commands.hpp"
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

  map<string, function<Command *()>> func = {
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
  string concat(const string &sep, const vector<string> &strs);
  void delete_commands(vector<Command *> commands);
  static vector<string> split(const string &s, char del, bool remove_comma);

public:
  Parser(string file);
  void preprocess();
  vector<Command *> get_commands();
  static Register get_register(const string &str);
  static vector<string> get_offset(const vector<string> &args);
  static bool is_number(const string &str);
  Command *get_command(const string &str);
  map<std::string, int> get_labels() { return labels; }

  static string exception_message(const string &command, int required,
                                  int provided) {
    return string("invalid amount of args in " + command + ": required " +
                  to_string(required) + ", provided " + to_string(provided));
  }


  // DEBUG print
  void print_macro() {
    for (const auto& element : macro) {
      std::cout << element.first << std::endl;
      Macro s = element.second;
      for (string w: s.params) {
        std::cout << w << std::endl;
      }
      for (string w: s.macro_lines) {
        std::cout << w << std::endl;
      }
    }
  }

};
