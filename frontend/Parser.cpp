#include "Parser.hpp"

std::map<std::string, Register> Parser::registers_names = {
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


std::vector<std::string> Parser::split(const std::string& s, char del, bool remove_comma) {
    std::vector<std::string> result;
    std::stringstream input(s);
    std::string item;

    while (getline (input, item, del)) {
        if (item.empty() || item[0] == '\t') { continue; }         // unused space
        if (item[0] == ';' || item[0] == '#') { return result; }   // comment start
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


std::string Parser::concat(const std::string& sep, const std::vector<std::string>& strs) {
    assert(!strs.empty());

    return std::accumulate(std::next(strs.cbegin()), strs.cend(), *strs.cbegin(),
        [&sep](string c, const string& s)
            { return std::move(c) + sep + s; });
}

std::vector<std::string> Parser::get_offset(const std::vector<std::string>& args) {
    std::vector<std::string> result;
    int offset = 0;
    result.push_back(args[0]);
    std::vector<std::string> tmp = split(args[1], '(', true);
    if (is_number(tmp[0])) {
        result.push_back(tmp[0]);
    } else {
        throw ParserException("Offset is not number");
    }
    result.push_back(tmp[1].erase(tmp[1].size() - 1, 1));
    return result;
}


int Parser::get_immediate(const std::string& str) {
    if (is_dec_number(str)) {
        return stoi(str);
    }
    if (is_hex_number(str)) {
        std::string buffer;
        int sign = 1;
        if (str.at(0) == '-') {
            buffer = str.substr(3);
            sign = -1;
        } else {
            buffer = str.substr(2);
        }
        return sign * stoi(buffer, nullptr, 16);
    }
    if (is_binary_number(str)) {
        std::string buffer;
        int sign = 1;
        if (str.at(0) == '-') {
            buffer = str.substr(3);
            sign = -1;
        } else {
            buffer = str.substr(2);
        }
        return sign * stoi(buffer, nullptr, 2);
    }
    throw new ParserException("Wrong number: " + str);
};


int Parser::is_binary_char(char c) {
    if (c != '0' && c != '1') {
        return 0;
    }
    return 1;
}


bool Parser::is_hex_char(char c) {
    if ('0' <= c && c <= '9') {
        return true;
    }
    if ('a' <= c && c <= 'f') {
        return true;
    }
    if ('A' <= c && c <= 'F') {
        return true;
    }
    return false;
}


bool Parser::is_binary_number(const std::string& str) {
    if (str.empty() || str.size() <= 2) return false;
    auto iter = str.begin();

    if (str.front() == '-') {
        if (str.size() <=3) {
            return false;
        }
        iter++;
    }
    

    if (*iter == '0' && *++iter == 'b') {
        iter++;
        return all_of(iter, str.end(), Parser::is_binary_char);
    }
    return false;
}


bool Parser::is_hex_number(const std::string& str) {
    if (str.empty() || str.size() <= 2) return false;
    auto iter = str.begin();

    if (str.front() == '-') {
        if (str.size() <=3) {
            return false;
        }
        iter++;
    }

    if (*iter == '0' && *++iter == 'x') {
        iter++;
        return all_of(iter, str.end(), Parser::is_hex_char);
    }
    return false;
}


bool Parser::is_dec_number(const std::string& str) {
    if (str.empty()) return false;
    auto iter = str.begin();

    if (str.front() == '-') {
        if (str.size() == 1) {
            return false;
        }
        iter++;
    }
    return all_of(iter, str.end(), ::isdigit);
}


bool Parser::is_number(const std::string& str) {
    return is_binary_number(str) || is_hex_number(str) || is_dec_number(str);
}


Register Parser::get_register(const std::string &str) {
    if (registers_names.find(str) != registers_names.end()) {
        return registers_names[str];
    }
    throw ParserException("invalid register: " + str);
}

Instruction* Parser::get_instruction(const std::string& str, std::vector<std::string> args) {
    if (func.find(str) != func.end()) {
        return func[str](args);
    }
    throw ParserException("invalid instruction: " + str);
}

void Parser::delete_instructions(vector<Instruction*> instructions) {
    for (Instruction* instruction : instructions) {
        delete instruction;
    }
}

std::vector<Instruction*> Parser::get_instructions() {
    std::vector<Instruction*> instruction_vector;
    std::ifstream in("_in.parse");
    if (in.is_open()) {
        std::string line;
        while (getline(in, line)) { 
            std::vector<std::string> buf = split(line, ' ', true);
            std::string start = buf.front();
            buf.erase(buf.begin());
            Instruction* instruction;
            try {
                instruction = get_instruction(start, buf);
            } catch (const ParserException& e) {
                delete_instructions(instruction_vector);
                in.close();
                throw;
            } 
            instruction_vector.push_back(instruction);
        }
    }
    in.close();
    return instruction_vector;
}

