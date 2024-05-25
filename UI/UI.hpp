#pragma once
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/node.hpp>      // for Render
#include <ftxui/screen/color.hpp> // for ftxui
#include <vector>
#include <string>
#include "../interpreter/Interpreter.hpp"
using namespace ftxui;
class UI {
    std::vector<std::string> all_lines_in;
    std::string reset_position;
    int n_lines;
    std::vector<Instruction *>& instructions;
    std::map<std::string, int>& labels;
    std::vector<int>& in_to_inparse;
    std::vector<int>& inparse_to_in;
    bool debug_flag;
    public:
    UI() = delete;
    UI(std::vector<Instruction *>& _instructions, std::map<std::string, int>& _labels, std::vector<std::string> _all_lines_in,
                                 std::vector<int>& _in_to_inparse, std::vector<int>& _inparse_to_in, bool _debug_flag):
        all_lines_in(_all_lines_in), 
        instructions(_instructions),
        labels(_labels),
        in_to_inparse(_in_to_inparse),
        inparse_to_in(_inparse_to_in),
        debug_flag(_debug_flag) {}

    void render(int line_number, State* state);
    void clean();
    std::string getline();
    void print(std::string s);
    auto render_registers(State* state);
    void start();
    ftxui::Element render_intsructions(int line_number = 0);
    ftxui::Element render_stack(State& state);
};