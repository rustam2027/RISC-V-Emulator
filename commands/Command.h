#pragma once
#include "../State.h"


struct Command {
  virtual void exec(State& state) = 0;
};
