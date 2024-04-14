#include "../instructions/Instruction.hpp"
#include <vector>
#include "../State.hpp"


class Interpreter {
  State* global_state;
  std::vector<Instruction*> commands;
public:
  Interpreter(std::vector<Instruction*> commands, std::map<std::string, int> labels);
  void interpret();
  ~Interpreter();
};
