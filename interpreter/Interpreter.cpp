#include "Interpreter.hpp"
#include <algorithm>
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

Interpreter::Interpreter(std::vector<Command *> commands,
                         std::map<std::string, int> labels) {
  this->commands = commands;
  global_state = new State(labels);
}

void Interpreter::interpret() {
  while (global_state->registers[pc] < commands.size()) {
    commands[global_state->registers[pc]]->exec(*global_state);
    global_state->registers[pc]++;
  }
}

Interpreter::~Interpreter() {
  for (Command *command : commands) {
    delete command;
  }
  delete global_state;
}
