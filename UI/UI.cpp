#include "UI.hpp"
#include "../frontend/Parser.hpp"
#include "padding.hpp"

#include <ftxui/dom/table.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <iostream>

#include <stdlib.h>

using namespace ftxui;

void UI::move_output(std::vector<std::string>& v) {
    for (int i = 0; i < 8; ++i) {
        v[i] = v[i + 1];
    }
    v.pop_back();
}


ftxui::Element UI::render_intsructions(int line_number, Interpreter& controller) {
    auto start = 0;
    Elements nums_elements, instructions_elements, output_elements;
    if (line_number > 31) {
        start = line_number - 15;
    }
    for (int j = start; j <= start + 31; j++) {
        auto num = text(std::to_string(j)) | align_right;
        if (controller.is_breakpoint(j)) {
            num = bgcolor(Color::Red, text(std::to_string(j)));
        }
    
        auto instruction = text(all_lines_in[j]);

        if (j == line_number) {
            instruction = bgcolor(Color::Red, text(all_lines_in[j]));
        }
        nums_elements.push_back(std::move(num));
        instructions_elements.push_back(std::move(instruction));
    }
    
    for (auto const& line : output) {
        auto out_line = text(line);
        output_elements.push_back(std::move(out_line));
    }
    return vbox({
        hbox({
            text(L"instructions") | padding(1) | flex,
    
        }),
        separator(),
        hbox({
            vbox({
                std::move(nums_elements),
            }) | padding(1) | size(WIDTH, EQUAL, 5) | size(HEIGHT, EQUAL, 40),
            separator(),
            vbox({
                std::move(instructions_elements)
            }) | padding(1) | size(HEIGHT, EQUAL, 100),
            filler(),
            
        }),
        separator(),
        hbox({text(L"OUTPUT") | padding(1) | flex}),
        
        hbox({
            vbox({
                std::move(output_elements)
            }) | padding(1) | size(HEIGHT, EQUAL, 30),
            filler(),
            
        })
    }) | border;
}
auto UI::render_registers(State* state) {
    std::vector<std::vector<std::string>> vec = {{"Register name", "Value"}}; 
    auto registers = Parser::get_register_names();


    for (auto const& reg : registers) {
        auto name = reg.first;
        auto value = std::to_string(state->registers[reg.second]);
        vec.push_back({name, value});


    }
    auto table = Table(vec);
    table.SelectColumn(0).Border(LIGHT);
    table.SelectColumn(1).Border(LIGHT);
    table.SelectRow(0).Decorate(bold);
    table.SelectRow(0).SeparatorVertical(LIGHT);
    table.SelectRow(0).Border(DOUBLE);
 
    table.SelectColumn(2).DecorateCells(align_right);

    return table;
}

auto UI::render_stack(State* state, int from, int to) {
    std::vector<std::vector<std::string>> vec = {{"  Number  ","Stack"}};
    for (int i = from; i < to; i++) {
        std::string num  = std::to_string(i * 8);
        long word = 0;
        for (int j = 0; j < 8; j++) {
            word = word << 8;
            word += (int)state->stack[i * 8 + j];
        }
        std::string value = Interpreter::get_hex(word);
        vec.push_back({num, value});
    }
    auto table = Table(vec);
    table.SelectColumn(0).Border(LIGHT);
    table.SelectColumn(1).Border(LIGHT);
    table.SelectRow(0).Decorate(bold);
    table.SelectRow(0).SeparatorVertical(LIGHT);
    table.SelectRow(0).Border(DOUBLE);
 

    return table;

}



void UI::render(int line_number, State* state, int from, int to, Interpreter& controller) {
    auto document = vbox({
            hbox({
                render_intsructions(line_number, controller) | flex,
    
                vbox({render_registers(state).Render() | flex,
                    }),
                vbox({render_stack(state, from, from + to).Render() | flex})
            }), 
            separator(),
    }) | size(HEIGHT, EQUAL, 43);

    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document.get());

    clean();
    std::cout << screen.ToString() << std::flush;
    reset_position = screen.ResetPosition();
    
}

void UI::clean() {
    std::cout << reset_position;
    n_lines = 200;
    if (n_lines) {
        std::cout << "\r" << "\x1B[2K";
        for (int i = 0; i < n_lines + 1; i ++) {
            std::cout << "\x1B[1A" << "\x1B[2K";
        }
    }

    n_lines = 0;
}

void UI::print(std::string s) {
    std::cout << s;
    for(auto const& ch : s) {
        if (ch == '\n') {
            n_lines++;
        }
    }
}

std::string UI::getline() {
    std::string str;
    std::getline(std::cin, str);
    n_lines++;
    return str;
}

void UI::clear_string() {
    std::cout << "\x1B[1A" << "\x1B[2K";
}

void UI::start() {
    Interpreter controller = Interpreter(instructions, labels, all_lines_in, in_to_inparse, inparse_to_in, debug_flag, true); 
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();

    while (controller.has_lines()) {
        auto line_num = controller.get_line();
        auto state = controller.get_state();

        std::string command;
        int from = 0;
        clean();
        while (controller.get_stop()) {
            render(line_num, state, from, from + 45, controller);
            print("> press N to step in, S to step over, O to step out and q or exit to quit\n");
            print("> ");
            command = getline();
            clear_string();
            if (command.rfind("show stack", 0) == 0) {
                    std::string to;
                    std::string buffer;
                    std::stringstream stream_request(command);
                    stream_request >> buffer >> buffer >> from >> to;
                    continue;
            }
            int exit_code = controller.process_request(command);
            if (exit_code) {
                render_output(exit_code, command);
            }
        }
        controller.interpret();
    }
}

void UI::render_output(int exit_code, std::string &command)
{
    std::string str;
    output.push_back(error_strings[exit_code] + command);
    if (output.size() > 7) {
        move_output(output);
    }
}
