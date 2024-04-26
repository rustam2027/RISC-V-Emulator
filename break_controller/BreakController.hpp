#pragma once

#include "../instructions/Instruction.hpp"
#include <bitset>
#include <vector>

class BreakController {
  std::vector<Instruction *> instructions_;
  std::bitset<100000> break_points;
  State* global_state;
  bool exit;

  void show_registers();
  void show_stack(size_t from, size_t to);

  void step_in();
  void next();

  void set_break_point();
  
  void show_context();

  void show_help();

public:
  BreakController(std::vector<Instruction *> instructions,
                  std::map<std::string, int> labels);

  void interpret();
  void open_interface();

  ~BreakController();
};
