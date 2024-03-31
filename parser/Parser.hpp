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
  static map<string, Register> registers_names;
  map<std::string, int> labels;

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
      {"bge", []() { return new BranchGreaterEqual(); }}};

  string file;
  vector<string> split(const string &s, char del, bool remove_comma);
  string concat(const string &sep, const vector<string> &strs);
  void delete_commands(vector<Command *> commands);

public:
  Parser(string file);
  void preprocess();
  vector<Command *> get_commands();
  static Register get_register(const string &str);
  static bool is_number(const string &str);
  Command *get_command(const string &str);
  map<std::string, int> get_labels() { return labels; }

  static string exception_message(const string &command, int required,
                                  int provided) {
    return string("invalid amount of args in " + command + ": required " +
                  to_string(required) + ", provided " + to_string(provided));
  }
};
