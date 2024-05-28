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
    std::map<int, std::string> error_strings = {
        {1, "> UNKNOWN COMMAND: "},
        {2, "> UNKNOWN LABEL: "},
        {3, "> NUMBER IS TOO BIG: "},
        {4, "> INVALID LINE (MAYBE MACROS DONT USE THEM!!!): "}
    };

    std::vector<std::string> all_lines_in;
    std::vector<std::string> output;

    std::stringstream output_stream;

    int n_lines;

    bool debug_flag;
    void move_output(std::vector<std::string>& v);

    Interpreter& controller;
    

    public:
    
        UI() = delete;
        UI(std::vector<std::string> _all_lines_in,
         bool _debug_flag, Interpreter& _controller):
            all_lines_in(_all_lines_in), 
            debug_flag(_debug_flag),
            controller(_controller) {}

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