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
    public:
    Interpreter controller;
    UI(std::vector<std::string> _all_lines_in, Interpreter _controller):
        all_lines_in(_all_lines_in), controller(_controller) {};

    void render();
    auto render_registers();
};