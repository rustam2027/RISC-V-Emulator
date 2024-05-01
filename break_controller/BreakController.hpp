#pragma once

#include <bitset>
#include <vector>

#include "../instructions/Instruction.hpp"

class BreakController {
    std::vector<Instruction *> instructions_;
    std::bitset<100000> break_points;
    State *global_state;
    bool exit;
    bool debug;
    
    void show_registers();
    void show_register(std::string rg);
    void show_stack(size_t from, size_t to);

    void step_in();
    void next();

    void set_break_point();

    void show_context();

    void show_help();

    std::vector<std::string> all_lines_in;

    std::vector<int> from_in_to_inparse;
    std::vector<int> from_inparse_to_in;

    std::string get_hex(long num);

   public:
    BreakController(std::vector<Instruction *>& instructions, std::map<std::string, int>& labels, std::vector<std::string>& all_lines,
                    std::vector<int>& in_to_inparse, std::vector<int>& inparse_to_in, bool debug);

    void interpret();
    void open_interface();

    ~BreakController();
};
