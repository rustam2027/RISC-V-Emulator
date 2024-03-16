#include "Interpreter.hpp"
#include <cstdio>
#include <vector>
#include <stdio.h>

Interpreter::Interpreter(std::vector<Command*> commands) {
  this->commands = commands;
}

void Interpreter::interpret() {
  while (global_state.registers[pc] < commands.size()) {
    commands[global_state.registers[pc]]->exec(global_state);
    global_state.registers[pc]++;
  }
  printf("%d", global_state.registers[a3]);
}

Interpreter::~Interpreter() {
  for (Command* command : commands) {
    delete command;
  }
}
