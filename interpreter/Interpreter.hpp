#include "../commands/Command.hpp"

#include "../State.hpp"


class Interpreter {
  State* global_state;
  std::vector<Command*> commands;
public:
  Interpreter(std::vector<Command*> commands, std::map<std::string, int> labels);
  void interpret();
  ~Interpreter();
};
