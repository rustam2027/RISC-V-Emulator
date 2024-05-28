#pragma once
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/node.hpp>      // for Render
#include <ftxui/screen/color.hpp> // for ftxui
#include <vector>
#include <string>
#include <sstream>
#include <streambuf>

#include "../interpreter/Interpreter.hpp"
using namespace ftxui;
class UI {

    std::string reset_position;
    std::map<std::string, int>& labels;
    std::map<int, std::string> error_strings = {
        {1, "> UNKNOWN COMMAND: "},
        {2, "> UNKNOWN LABEL: "},
        {3, "> NUMBER IS TOO BIG: "},
        {4, "> INVALID LINE (MAYBE MACROS DONT USE THEM!!!): "}
    };

    std::vector<std::string> all_lines_in; // FIXME: HELL!!!
    std::vector<Instruction *>& instructions;
    std::vector<int>& in_to_inparse;
    std::vector<int>& inparse_to_in;
    std::vector<std::string> output;

    std::stringstream output_stream;

    int n_lines;

    bool debug_flag;
    void move_output(std::vector<std::string>& v);
    

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

        void render(int line_number, State* state, int from, int to, Interpreter& controller);
        void clean();
        void clear_string();
        std::string getline();
        void print(std::string s);
        auto render_registers(State* state);
        void start();
        void render_output(int exit_code, std::string &command);
        ftxui::Element render_intsructions(int line_number, Interpreter &controller);
        auto render_stack(State* state, int from, int to );
};