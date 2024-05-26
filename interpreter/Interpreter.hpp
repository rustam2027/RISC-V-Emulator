#pragma once

#include <bitset>
#include <vector>

#include "../instructions/Instruction.hpp"


class Interpreter { 
    std::vector<Instruction *> instructions_;

    std::bitset<100000> break_points;
    std::bitset<100000> set_manually;

    State *global_state;
    bool exit;
    bool debug;
    bool stop;
    bool graph_flag;
    bool break_on_next = false;

    bool first_instruction = true;
    
    void show_registers();
    void show_register(std::string rg);
    void show_stack(size_t from, size_t to);

    int breakpoint_set_by_label(std::string label);
    int breakpoint_set_by_number(int num);

    void step_over();
    void step_in();
    void step_out();

    void show_context();

    void show_help();

    std::vector<std::string>& all_lines_in;

    std::vector<int>& from_in_to_inparse;
    std::vector<int>& from_inparse_to_in;


   public:
    Interpreter(std::vector<Instruction *>& instructions, std::map<std::string, int>& labels, std::vector<std::string>& all_lines,
                    std::vector<int>& in_to_inparse, std::vector<int>& inparse_to_in, bool debug, bool graph);

    int get_line();

    const State* get_stack() const { return global_state; };

    void interpret();
    int process_request(std::string command);

    bool has_lines();

    void open_interface();
    static std::string get_hex(long num);
    bool get_stop() {
        return stop && !exit;
    }
    State* get_state() {
        return global_state;
    }

    bool is_breakpoint(size_t num);

    ~Interpreter();
};
