#include "Parser.h"

Parser::Parser(string file): file(file) {}


vector<string> Parser::split(const string &s, char del) {
    vector<string> result;
    stringstream input(s);
    string item;

    while (getline (input, item, del)) {
        int last = item.size() - 1;
        if (item[last] == ',') {
            item.erase(last, 1);
        }
        result.push_back (item);
    }
    return result;
}


Register Parser::get_register(string str) {
    if (registers_names.find(str) != registers_names.end()) {
        return registers_names[str];
    }
    throw 77; // not optional<Register>, it's not a normal situation
}

vector<Command*> Parser::get_next() {
    ifstream in(file);
    if (in.is_open()) {
        while (getline(in, line)) { 
          vector<string> buf = split(line, ' ');
        //   for (string s: buf) {
        //     cout << s << endl;
        //   }
        }
    }
    in.close();
    
    vector<Command*> command_vector;
    return command_vector;
}

