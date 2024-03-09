#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "commands/Command.h"

using namespace std;

class Parser {
 private: 
  string file;
  string line;
 public:
  Parser(string file);
  vector<Command*> get_next();
};