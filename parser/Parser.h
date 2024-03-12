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
    map <string, Register> registers_names = {
      {"zero", zero}, {"ra", ra}, {"sp", sp},
      {"gp", gp}, {"tp", tp}, {"pc", pc},
      {"t0", t0}, {"t1", t1}, {"t2", t2},
      {"t3", t3}, {"t4", t4}, {"t5", t5},
      {"t6", t6}, {"s0", s0}, {"s1", s1},
      {"s2", s2}, {"s3", s3}, {"s4", s4},
      {"s5", s5}, {"s6", s6}, {"s7", s7},
      {"s8", s8}, {"s9", s9}, {"s10", s10},
      {"s11", s11}, {"a0", a0}, {"a1", a1},
      {"a2", a2}, {"a3", a3}, {"a4", a4},
      {"a5", a5}, {"a6", a6}, {"a7", a7} 
    };

    map <string, function<Command*(Register)>> func = {
      {"add", [](Register r) { return new Add(r, r, r);}},
      {"and", [](Register r) { return new And(r, r, r);}}
    };

    string file;
    string line;
    Register get_register(string str);
    vector<string> split (const string &s, char del);
  public:
    Parser(string file);
    vector<Command*> get_next();
};
