#include "UI.hpp"
#include "../frontend/Parser.hpp"
// #include "padding.hpp"

#include <ftxui/dom/table.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>
using namespace ftxui;
auto UI::render_registers() {
    auto state = controller.get_state();
    Elements elements;
    Elements current_line;
    std::vector<std::vector<std::string>> vec = {{"Register name", "Value"}}; 

    for (auto const& reg : Parser::get_register_names()) {
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

    auto content = table.SelectRows(1, -1);

    return table;
}

void UI::render() {
    auto d = //
      vbox({
          hbox({
              text("north-west"),
              filler(),
              text("north-east"),
          }),
          filler(),
          hbox({
              filler(),
              text("center"),
              filler(),
          }),
          filler(),
          hbox({
              text("south-west"),
              filler()
          }),
    }) | flex;
    auto document = //
        vbox({
            render_registers().Render()
            }) | flex;
    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document.get());
    screen.Print();
    
}