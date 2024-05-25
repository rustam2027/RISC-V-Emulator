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
    public:
    UI() = delete;
    UI(std::vector<std::string> _all_lines_in):
        all_lines_in(_all_lines_in) {};

    void render(int line_number);
    void clean();
    std::string getline();
    void print(std::string s);
    auto render_registers(State& state);
    void start();
    ftxui::Element render_intsructions(int line_number = 0);
    ftxui::Element render_stack(State& state);
};