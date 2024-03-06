#include "State.h"
#include "Register.h"
#include "commands/Command.h"

#include "commands/Add.cpp"
#include "commands/Li.cpp"

#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
  // string file;
  // if (argc > 1) {
  //   file = argv[1];
  // } else {
  //   cout << "NO incoming file" << endl;
  //   file = "in.txt";
  // }

  State st = State();
  Li f1 = Li{a1, 8};

  vector<Command> command_vector(3);

  command_vector.push_back(f1);
  command_vector.push_back(Li{a2, 8});
  command_vector.push_back(Add{a3, a1, a2});

  while (!command_vector.empty()) {
    command_vector.back().exec(st);
    command_vector.pop_back();
  }

  printf("%d", st.registers[a3]);


  // string line;
  // ifstream in(file);
  // if (in.is_open()) {
  //   while (getline(in, line)){ 
  //     cout << line << endl;
  //   }
  // }
  // in.close();

  // printf("%d %d\n", st.registers[a1], a1);

  return 0;
}
