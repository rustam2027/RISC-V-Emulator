#include "Parser.h"

Parser::Parser(string file): file(file) {}

vector<Command*> Parser::get_next() {
    ifstream in(file);
    if (in.is_open()) {
        while (getline(in, line)){ 
          cout << line << endl;
        }
    }
    in.close();
    
    vector<Command*> command_vector;
    return command_vector;
}
