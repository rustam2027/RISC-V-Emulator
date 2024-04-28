#pragma once
#include "../State.hpp"
#include <vector>
#include <string>


struct Instruction {
  virtual void exec(State& state) = 0;
  virtual ~Instruction() = default;
};
