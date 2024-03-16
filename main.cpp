
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
    cout << "NO incoming file" << endl; 
    // throw file exception
    file = "in.txt";
  }

  Parser parser = Parser(file);
  Interpreter interpreter(parser.get_commands());

  try {
    interpreter.interpret();
  } catch (const int error_num) {
    cout << error_num << endl;
  }

  return 0;
}
