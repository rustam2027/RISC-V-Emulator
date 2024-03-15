#pragma once
#include "../State.h"
#include <vector>
#include <string>


struct Command {
  virtual void exec(State& state) = 0;
  virtual void fill_args(std::vector<std::string> args) = 0;
  virtual ~Command() = default;
};
