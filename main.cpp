#include <cstring>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

#include "UI/UI.hpp"
#include "exceptions/ArgsParsingException.hpp"
#include "exceptions/ParserException.hpp"
#include "exceptions/PreprocessorException.hpp"
#include "exceptions/RuntimeException.hpp"
#include "frontend/Parser.hpp"
#include "frontend/Preprocessor.hpp"
#include "frontend/StringUtils.hpp"
#include "instructions/Instruction.hpp"
#include "interpreter/Interpreter.hpp"
#include "tests/simple_instructions_test.hpp"

int main(int argc, char* argv[]) {
    bool debug_mode = false;
    bool graph_mode = false;

    if (argc == 1) {
        cout << "No incoming file" << endl;
        exit(1);
    }

    const string file = argv[1];

    try {
        std::set<FLAGS> flags = StringUtils::parse_args(argc, argv);
        if (flags.contains(d)) {
            debug_mode = true;
        }
        if (flags.contains(g)) {
            graph_mode = true;
        }
    } catch (const ArgsParsingExceprion& e) {
        cout << e.get_message() << endl;
        exit(1);
    }


    Preprocessor preprocessor = Preprocessor(file);

    try {
        preprocessor.preprocess();
    } catch (const PreprocessorException& e) {
        cout << e.get_message() << endl;
        exit(1);
    }

    Lexer lexer(preprocessor.get_inparse());

    Parser parser(lexer, preprocessor.get_labels(), preprocessor.get_from_inparse_to_in());
    vector<Instruction*> instructions;
    try {
        instructions = parser.get_instructions();
    } catch (const ParserException& e) {
        cout << e.get_message() << endl;
        exit(1);
    }

    auto all_lines_in = preprocessor.all_lines_in();

    Interpreter controller(instructions, preprocessor.get_labels(), all_lines_in, preprocessor.get_from_in_to_inparse(),
                           preprocessor.get_from_inparse_to_in(), debug_mode, graph_mode);
    if (graph_mode) {
        UI ui(all_lines_in, debug_mode, controller);
        ui.start();
    } else {
        try {
            if (debug_mode && controller.has_lines()) {
                controller.open_interface();
            }

            while (controller.has_lines()) {
                controller.interpret();
                if (debug_mode && controller.has_lines()) {
                    controller.open_interface();
                }
            }
            if (debug_mode && controller.is_break()) {
                controller.open_interface();
            }
        } catch (const RuntimeException& e) {
            cout << e.get_message() << endl;
            exit(1);
        }
    }

    // preprocessor.dump_inparse();
    // test_all();
    return 0;
}
