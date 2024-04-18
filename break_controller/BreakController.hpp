#include <vector>
#include "../instructions/Instruction.hpp"


class BreakController {
public:
  void interpret(std::vector<Instruction*> instructions);
  void open_interface();
};
