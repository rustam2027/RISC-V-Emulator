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


vector<string> Parser::split(const string& s, char del, bool remove_comma) {
    vector<string> result;
    stringstream input(s);
    string item;

    while (getline (input, item, del)) {
        if (item.empty() || item[0] == '\t') { continue; }  // unused space
        if (item[0] == ';' || item[0] == '#') { return result; } //comment start
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

vector<string> Parser::get_offset(const vector<string>& args) {
    vector<string> result;
    int offset = 0;
    result.push_back(args[0]);
    vector<string> tmp = split(args[1], '(', true);
    if (is_number(tmp[0])) {
        result.push_back(tmp[0]);
    } else {
        throw ParserException("Offset is not int");
    }
    result.push_back(tmp[1].erase(tmp[1].size() - 1, 1));
    return result;
}


string Parser::concat(const string& sep, const vector<string>& strs) {
    assert(!strs.empty());

    return std::accumulate(std::next(strs.cbegin()), strs.cend(), *strs.cbegin(),
        [&sep](string c, const string& s)
            { return std::move(c) + sep + s; });
}


void Parser::string_replace(string& input, const string& src, const string& dst) {
    size_t pos = input.find(src);
    while(pos != string::npos) {
        input.replace(pos, src.size(), dst);
        pos = input.find(src, pos);
    }
}


bool Parser::is_number(const string& str) {
    if (str.empty()) return false;
    auto iter { str.begin() };
    if (str.front() == '-') {
      if (str.size() > 1) ++iter; // neg number
      else return false;          // only -
    }
    return all_of(iter, str.end(), ::isdigit);
  }


Register Parser::get_register(const string &str) {
    if (registers_names.find(str) != registers_names.end()) {
        return registers_names[str];
    }
    throw ParserException("invalid register: " + str);
}

Instruction* Parser::get_command(const string &str) {
    if (func.find(str) != func.end()) {
        return func[str]();
    }
    throw CommandCreationException("invalid command: " + str);
}

void Parser::delete_commands(vector<Instruction*> commands) {
    for (Instruction* command : commands) {
        delete command;
    }
}

vector<Instruction*> Parser::get_commands() {
    vector<Instruction*> command_vector;
    ifstream in("_in.parse");
    if (in.is_open()) {
        string line;
        while (getline(in, line)) { 
            vector<string> buf = split(line, ' ', true);
            string start = buf.front();
            buf.erase(buf.begin());
            Instruction* command;
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
    int counter = 0;  // counter for lines in _in.parse
    if (in.is_open()) {
        std::string current_line;
        while (getline(in, current_line)) { 
            if (current_line.empty() || current_line[0] == ';' || current_line[0] == '#') {
                continue;
            }
            vector<string> buf = split(current_line, ' ', false);
            if (buf.empty()) { continue; }
            string first = buf.front();
            if (macro.find(first) != macro.end()) {
                buf = split(current_line, ' ', true);  // delete ,
                buf.erase(buf.begin());
                if (macro[first].params.size() != buf.size()) {
                     throw ParserException("invalid args amount for macro: " + first);
                }
                for (string line: macro[first].macro_lines) {
                    for (size_t i = 0; i < macro[first].params.size(); i++) {
                        string_replace(line, macro[first].params[i], buf[i]);
                    }
                    counter++;
                    out << line << endl; 
                }
                continue;
            }
            if (first.at(0) == '.') {
                if (first == ".macro") {
                    Parser::Macro m_data;
                    string name = buf[1];
                    buf = split(current_line, ' ', true);     // delete ,
                    buf.erase(buf.begin(), buf.begin() + 2);  // delete .macro and macro_name
                    m_data.params = buf;                      // many parameters
                    while (getline(in, current_line)) {
                        vector<string> in_buf = split(current_line, ' ', false);  // delete comments
                        if (in_buf.front() == ".end_macro") { break; }
                        m_data.macro_lines.push_back(concat(" ", in_buf)); 
                    }
                    macro[name] = m_data;
                }
                // can be .text .data .bss .equ --> switch 
                // iterate line for one-line situations: .section .text
                continue;
            }
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
