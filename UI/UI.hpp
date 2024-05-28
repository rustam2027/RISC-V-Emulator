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
    const static int ERROR_CODE_FOR_SR = 5;
    std::string reset_position;
    std::map<int, std::string> error_strings = {
        {0, ""},
        {1, "> UNKNOWN COMMAND: "},
        {2, "> UNKNOWN LABEL: "},
        {3, "> NUMBER IS TOO BIG: "},
        {4, "> INVALID LINE (MAYBE MACROS DONT USE THEM!!!): "},
        {5, "> THIS COMMAND IS NOT ALLWOED IN GUI: "},
        {6, "- continue (c): Continue execution until the next breakpoint or the end of the program."},
        {7, "- exit (q): Exit the debugger."},
        {8, "- show memory <from> <to>: Show the stack contents from address <from> to <to>."},
        {9, "- step in (s): Execute the next instruction and step into any function calls."},
        {10, "- step over (n): Execute the next instruction and skip over any function calls."},
        {11, "- step out (o): Execute until the current function returns."},
        {12, "- help: Show this help message."}
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
        void render_help();
        void clear_output();
        void render_output(int exit_code, std::string &command);
        ftxui::Element render_intsructions(int line_number, Interpreter &controller);
        auto render_stack(State* state, int from, int to );
};