
#include "tests/simple_commands_test.h"
#include "parser/Parser.h"
#include "commands/Command.h"
#include "commands/commands.h"

#include <iostream>
#include <vector>


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
  State st = State();


  try {
    vector<Command*> commands = parser.get_next();
    for (Command* command : commands) {
      command->exec(st);
    }
    printf("%d\n", st.registers[a1]);
    printf("%d\n", st.registers[a2]);
    printf("%d\n", st.registers[a3]);
  } catch (const int error_num) {
    cout << error_num << endl;
  }

  // delete commands at the end --- LEAK MEMORY ---
  return 0;
}
