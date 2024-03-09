#include "State.h"
#include "Register.h"
#include "Parser.h"
#include "commands/Command.h"
#include "commands_impl.h"

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
  string file;
  if (argc > 1) {
    file = argv[1];
  } else {
    cout << "NO incoming file" << endl;
    file = "in.txt";
  }

  State st = State();
  Li f1 = Li{a1, 8};
  Li f2 = Li{a2, 8};
  Add a = Add{a3, a1, a2};

  std::vector<Command*> command_vector;

  command_vector.push_back(&f1);
  command_vector.push_back(&f2);
  command_vector.push_back(&a);

  for (Command* command : command_vector) {
    printf("LOL\n");
    command->exec(st);
  }
  printf("%d\n", st.registers[a1]);
  printf("%d\n", st.registers[a2]);
  printf("%d\n", st.registers[a3]);

  return 0;
}
