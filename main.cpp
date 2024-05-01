
#include <iostream>

#include "break_controller/BreakController.hpp"
#include "exceptions/ParserException.hpp"
#include "exceptions/PreprocessorException.hpp"
#include "exceptions/RuntimeException.hpp"
#include "frontend/Parser.hpp"
#include "frontend/Preprocessor.hpp"
#include "instructions/Instruction.hpp"
#include "instructions/instructions.hpp"
#include "interpreter/Interpreter.hpp"
#include "tests/simple_instructions_test.hpp"

int main(int argc, char *argv[]) {
  string file;
  bool debug_mode = false;

  if (argc > 1) {
    file = argv[1];
    if ((argc > 2) && (strcmp(argv[2], "-d") == 0)) {
      debug_mode = true;
    }
  } else {
    cout << "No incoming file" << endl;
    exit(1);
  }

  Preprocessor preprocessor = Preprocessor(debug_mode, file);

  try {
    preprocessor.preprocess();
  } catch (const PreprocessorException &e) {
    cout << e.get_message() << endl;
    exit(1);
  }

  Parser *parser = new Parser();
  vector<Instruction *> commands;
  try {
    commands = parser->get_instructions();
  } catch (const ParserException &e) {
    delete parser;  // to call lexer destructor
    cout << e.get_message() << endl;
    exit(1);
  }
  delete parser;

  if (debug_mode) {
    BreakController controller(commands, preprocessor.get_labels(), preprocessor.all_lines_in(), preprocessor.get_from_in_to_inparse(), preprocessor.get_from_inparse_to_in(), debug_mode);

    try {
      controller.interpret();
    } catch (const RuntimeException &e) {
      cout << e.get_message() << endl;
      exit(1);
    }

  } else {
    Interpreter interpreter(commands, preprocessor.get_labels());

    try {
      interpreter.interpret();
    } catch (const RuntimeException &e) {
      cout << e.get_message() << endl;
      exit(1);
    }
  }

  // test_all();
  return 0;
}
