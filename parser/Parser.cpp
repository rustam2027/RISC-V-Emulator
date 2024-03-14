#include "Parser.h"

Parser::Parser(string file): file(file) {}

map<string, Register> Parser::registers_names = {
      {"zero", zero}, {"ra", ra}, {"sp", sp},
      {"gp", gp}, {"tp", tp}, {"pc", pc},
      {"t0", t0}, {"t1", t1}, {"t2", t2},
      {"t3", t3}, {"t4", t4}, {"t5", t5},
      {"t6", t6}, {"s0", s0}, {"s1", s1},
      {"s2", s2}, {"s3", s3}, {"s4", s4},
      {"s5", s5}, {"s6", s6}, {"s7", s7},
      {"s8", s8}, {"s9", s9}, {"s10", s10},
      {"s11", s11}, {"a0", a0}, {"a1", a1},
      {"a2", a2}, {"a3", a3}, {"a4", a4},
      {"a5", a5}, {"a6", a6}, {"a7", a7} 
};


vector<string> Parser::split(const string &s, char del) {
    //TODO: check syntax errors, throw exception
    vector<string> result;
    stringstream input(s);
    string item;

    while (getline (input, item, del)) {
        int last = item.size() - 1;
        if (item[last] == ',') {
            item.erase(last, 1);
        }
        result.push_back(item);
    }
    return result;
}


Register Parser::get_register(const string &str) {
    if (registers_names.find(str) != registers_names.end()) {
        return registers_names[str];
    }
    throw 77; // not optional<Register>, it's not a normal situation
}

vector<Command*> Parser::get_next() {
    vector<Command*> command_vector;
    ifstream in(file);
    if (in.is_open()) {
        while (getline(in, line)) { 
          vector<string> buf = split(line, ' ');
          string start = buf.front();
          Command* command = func[start]();
          buf.erase(buf.begin());
          command->fill_args(buf);
          command_vector.push_back(command);
        }
    }
    in.close();
    return command_vector;
}

