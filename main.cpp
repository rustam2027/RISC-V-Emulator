
#include "tests/simple_commands_test.hpp"
#include "parser/Parser.hpp"
#include "commands/Command.hpp"
#include "commands/commands.hpp"
#include "interpreter/Interpreter.hpp"

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
  vector<Command*> commands;
  try {
    parser.preprocess();
    commands = parser.get_commands();
  } catch (ParserException e) {
    cout << e.get_message() << endl;
    exit(1);
  }

  Interpreter interpreter(commands, parser.get_labels());

  try {
    interpreter.interpret();
  } catch (const int error_num) {  // catch custom interpreter exception
    cout << error_num << endl;
  } 

  return 0;
}
