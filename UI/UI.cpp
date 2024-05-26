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

Component Wrap(std::string name, Component component) {
  return Renderer(component, [name, component] {
    return hbox({
               text(name) | size(WIDTH, EQUAL, 8),
               separator(),
               component->Render() | xflex,
           }) |
           xflex;
  });
}


ftxui::Element UI::render_intsructions(int line_number) {
    auto i = 1;
    Elements nums_elements, instructions_elements;
    for(auto const& line : all_lines_in) {
        auto num = text(std::to_string(i)) | align_right;
    
        auto instruction = text(line);
        // std::cout << i << " " << line_number << std::endl;
        if (i == line_number) {
            // std::cout << i << " " << line_number << std::endl;
            instruction = bgcolor(Color::Red, text(line));
        }
        nums_elements.push_back(std::move(num));
        instructions_elements.push_back(std::move(instruction));
        // std::cout << line << endl;
        // std::cout << i << endl;
        i++;
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
        })
    }) | border;
}
auto UI::render_registers(State* state) {
    std::vector<std::vector<std::string>> vec = {{"Register name", "Value"}}; 
    auto registers = Parser::get_register_names();
    // for (auto const& i : registers) {
    //     std::cout << i.first << std::endl;
    // }

    for (auto const& reg : registers) {
        auto name = reg.first;
        auto value = std::to_string(state->registers[reg.second]);
        vec.push_back({name, value});
        // std::cout << name << " " << value << std::endl;


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

auto UI::render_stack(State* state, int from, int to = 45) {
    std::vector<std::vector<std::string>> vec = {{"Byte number","Stack"}};
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
 
    // table.SelectColumn(2).DecorateCells(align_right);

    return table;

}



void UI::render(int line_number, State* state, int from, int to = 45) {
    auto document = vbox({
            hbox({
                render_intsructions(line_number) | flex,
                hbox({render_registers(state).Render() | flex}),
                vbox({render_stack(state, from, from + to).Render() | flex})
            }), 
            separator(),
    }) | size(HEIGHT, EQUAL, 45);

    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document.get());

    clean();
    std::cout << screen.ToString() << std::flush;
    reset_position = screen.ResetPosition();
    
}

void UI::clean() {
    std::cout << reset_position;
    n_lines = 1000;
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
void UI::start() {
    Interpreter controller = Interpreter(instructions, labels, all_lines_in, in_to_inparse, inparse_to_in, debug_flag); 
    /* Надо придумать услвоие для остановки. Что-то типа:
    while(controller.has_lines()) {
        
    }
    */ 
    while (controller.has_lines()) {
        clean();
        auto line_num = controller.get_line();
        auto state = controller.get_state();

        std::string command;
        
        while (controller.get_stop()) {
            render(line_num, state, 8);
            print("> press N to step in, S to step over, O to step out and q or exit to quit\n");
            print("> ");
            command = getline();
            controller.process_request(command); 
        }
        controller.interpret();
    }
}