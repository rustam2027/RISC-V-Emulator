#include "../commands/Command.hpp"

#include "../State.hpp"


class Interpreter {
  State global_state{};
  std::vector<Command*> commands;
public:
  Interpreter(std::vector<Command*> commands);
  void interpret();
  ~Interpreter();
};
