#pragma once
#include "../State.h"


struct Command {
  void exec(State& state);
};
