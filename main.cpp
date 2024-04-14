
#include "tests/simple_instructions_test.hpp"
#include "parser/Parser.hpp"
#include "instructions/Instruction.hpp"
#include "instructions/instructions.hpp"
#include "interpreter/Interpreter.hpp"

#include "exceptions/ParserException.hpp"
#include "exceptions/RuntimeException.hpp"

#include <iostream>


int main(int argc, char *argv[]){
  string file;
  if (argc > 1) {
    file = argv[1];
  } else {
    cout << "No incoming file" << endl; 
    exit(1);
  }

  Parser parser = Parser(file);
  vector<Instruction*> commands;
  try {
    parser.preprocess();
    commands = parser.get_instructions();
  } catch (const ParserException& e) {
    cout << e.get_message() << endl;
    exit(1);
  }

  Interpreter interpreter(commands, parser.get_labels());

  try {
    interpreter.interpret();
  } catch (const RuntimeException& e) { 
    cout << e.get_message() << endl;
    exit(1);
  } 

  test_all();
  return 0;
}
