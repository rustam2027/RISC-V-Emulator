#include "Parser.hpp"


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


vector<string> Parser::split(const string &s, char del, bool remove_comma) {
    //TODO: check syntax errors, throw exception
    vector<string> result;
    stringstream input(s);
    string item;

    while (getline (input, item, del)) {
        if (item.empty()) { continue; }  // unused space
        if (item[0] == ';') { return result; } //comment start
        if (remove_comma) {
            int last = item.size() - 1;
            if (item[last] == ',') {
                item.erase(last, 1);
            }
        }
        result.push_back(item);
    }
    return result;
}


string Parser::concat(const string &sep, const vector<string> &strs) {
    assert(!strs.empty());

    return std::accumulate(std::next(strs.cbegin()), strs.cend(), *strs.cbegin(),
        [&sep](string c, const string& s)
            { return std::move(c) + sep + s; });
}


Register Parser::get_register(const string &str) {
    if (registers_names.find(str) != registers_names.end()) {
        return registers_names[str];
    }
    throw ParserException("invalid register: " + str);
}

Command* Parser::get_command(const string &str) {
    if (func.find(str) != func.end()) {
        return func[str]();
    }
    throw CommandCreationException("invalid command: " + str);
}

void Parser::delete_commands(vector<Command*> commands) {
    for (Command* command : commands) {
        delete command;
    }
}

vector<Command*> Parser::get_commands() {
    vector<Command*> command_vector;
    ifstream in("_in.parse");
    if (in.is_open()) {
        string line;
        while (getline(in, line)) { 
            vector<string> buf = split(line, ' ', true);
            string start = buf.front();
            buf.erase(buf.begin());
            Command* command;
            try {
                command = get_command(start);
                command->fill_args(buf);
            } catch (CommandCreationException e) {
                delete_commands(command_vector);
                in.close();
                throw;
            } catch (ParserException e) {
                delete_commands(command_vector);
                delete command;
                in.close();
                throw;
            } 
            command_vector.push_back(command);
        }
    }
    in.close();
    return command_vector;
}

void Parser::preprocess() {
    ifstream in(file);
    std::ofstream out;
    out.open("_in.parse"); 
    int counter = 0;
    if (in.is_open()) {
        std::string current_line;
        while (getline(in, current_line)) { 
            if (current_line.empty() || current_line[0] == ';') {
                continue;
            }
            vector<string> buf = split(current_line, ' ', false);
            string first = buf.front();
            int last = first.size() - 1;
            if (buf.front()[last] == ':') {
                if (buf.size() == 1) {
                    first.erase(last, 1);
                    labels[first] = counter;
                    continue; 
                }
                out.close();
                in.close();
                throw ParserException("invalid label name: " + concat(" ", buf));
            }
            counter++;
            current_line = concat(" ", buf);
            out << current_line << endl;             
        }
    }
    out.close();
    in.close();
}

