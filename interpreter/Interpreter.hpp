#include "../instructions/Instruction.hpp"
#include <vector>
#include "../State.hpp"


class Interpreter {
  State* global_state;
  std::vector<Instruction*> instructions;
public:
  Interpreter(std::vector<Instruction*> instructions, std::map<std::string, int> labels);
  void interpret();
  ~Interpreter();
};
