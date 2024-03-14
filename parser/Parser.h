#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <optional>
#include <functional>
#include "../commands/Command.h"
#include "../commands/commands.h"

using namespace std;

class Parser {
  private: 
    static map<string, Register> registers_names;
    
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
    };

    string file;
    string line;
    vector<string> split (const string &s, char del);
  public:
    Parser(string file);
    vector<Command*> get_next();
    static Register get_register(const string &str);
};
