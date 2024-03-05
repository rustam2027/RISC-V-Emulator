#include "State.h"
#include "Register.h"
#include "commands/Add.cpp"
#include "commands/Li.cpp"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

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
  f1.exec(st);


  string line;
  ifstream in(file);
  if (in.is_open()) {
    while (getline(in, line)){ 
      cout << line << endl;
    }
  }
  in.close();

  printf("%d %d\n", st.registers[a1], a1);

  return 0;
}
