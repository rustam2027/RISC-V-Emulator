#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <functional>
#include <cstddef>
#include <numeric>
#include <cassert>

#include "../commands/Command.hpp"
#include "../commands/commands.hpp"
#include "../exceptions/ParserException.hpp"

using namespace std;

class Parser {
  private: 
    static map<string, Register> registers_names;
    map<std::string, int> labels;
    
    map <string, function<Command*()>> func = {
      {"add", []() { return new Add();}},
      {"addi", []() { return new Addi();}},
      {"and", []() { return new And();}},
      {"li", []() { return new Li();}},
      {"mv", []() { return new Mv();}},
      {"or", []() { return new Or();}},
      {"sll", []() { return new SLL();}},
      {"srl", []() { return new SRL();}},
      {"sub", []() { return new Sub();}},
      {"xor", []() { return new Xor();}},
      {"ecall", []() { return new Ecall();}}
    };

    string file;
    string line;
    vector<string> split(const string& s, char del, bool remove_comma);
    string concat(const string& sep, const vector<string>& strs);
    void preprocess();
  public:
    Parser(string file);
    vector<Command*> get_commands();
    static Register get_register(const string &str);
    static string exception_message(const string& command, int required, int provided) {
      return string("invalid amount of args in " + command + ": required " + to_string(required) + ", provided " + to_string(provided));
    }

};
