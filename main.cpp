#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <cstring>
#include "interpreter/Interpreter.hpp"
#include "exceptions/ParserException.hpp"
#include "exceptions/PreprocessorException.hpp"
#include "exceptions/RuntimeException.hpp"
#include "frontend/Parser.hpp"
#include "frontend/Preprocessor.hpp"
#include "instructions/Instruction.hpp"
#include "tests/simple_instructions_test.hpp"
#include "UI/UI.hpp"



int main(int argc, char *argv[]) {
  string file;
  bool debug_mode = false;
  bool graph_mode = false;

  if (argc > 1) {
    file = argv[1];
    if ((argc > 2) ) {
      if (strcmp(argv[2], "-d") == 0) {
        debug_mode = true;
      }
      else if (strcmp(argv[2], "-g") == 0) {
        graph_mode = true;
        debug_mode = true;
      }
    }
  } else {
    cout << "No incoming file" << endl;
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

  Parser parser(lexer, preprocessor.get_labels());
  vector<Instruction*> instructions;
  try {
    instructions = parser.get_instructions();
  } catch (const ParserException& e) {
    cout << e.get_message() << endl;
    exit(1);
  }
  
  auto all_lines_in = preprocessor.all_lines_in();
  
  if (graph_mode){
    UI ui(instructions, preprocessor.get_labels(), all_lines_in, preprocessor.get_from_in_to_inparse(), preprocessor.get_from_inparse_to_in(), debug_mode);
    ui.start();
  } else if (debug_mode){
      Interpreter controller(instructions, preprocessor.get_labels(), all_lines_in, preprocessor.get_from_in_to_inparse(), preprocessor.get_from_inparse_to_in(), debug_mode);
      try {
        while (controller.has_lines()) {
          controller.interpret();
          if (debug_mode && controller.has_lines()) {
            controller.open_interface();
          }
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