#pragma once

#include "../instructions/Instruction.hpp"
#include <vector>

class BreakController {
  std::vector<Instruction *> instructions_;
  State* global_state;
  bool exit;

  void show_registers();
  void show_stack(size_t from, size_t to);

public:
  BreakController(std::vector<Instruction *> instructions,
                  std::map<std::string, int> labels);

  void interpret();
  void open_interface();

  ~BreakController();
};
