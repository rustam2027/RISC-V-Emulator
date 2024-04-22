#include "../instructions/Instruction.hpp"
#include <vector>

class BreakController {
  std::vector<Instruction *> instructions;
  State* global_state;

  void show_registers();
  void show_stack(size_t from, size_t to);

public:
  BreakController(std::vector<Instruction *> instructions,
                  std::map<std::string, int> labels);

  void interpret();
  void open_interface();

  ~BreakController();
};
