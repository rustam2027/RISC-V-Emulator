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

std::vector<std::string> Parser::get_offset(const std::vector<std::string>& args) {
    std::vector<std::string> result;
    result.push_back(args[0]);
    std::vector<std::string> tmp = StringUtils::split(args[1], '(');
    if (tmp.size() < 2) {
        throw ParserException("Offset - need opening bracket");
    }
    if (is_number(tmp[0])) {
        result.push_back(tmp[0]);
    } else {
        throw ParserException("Offset is not a number");
    }
    int last = tmp[1].size() - 1;
    if (tmp[1][last] != ')') {
        throw ParserException("Offset - need closing bracket");
    }
    result.push_back(tmp[1].erase(last, 1));
    return result;
}


long Parser::get_immediate(const std::string& str) {
    if (is_dec_number(str)) {
        return stol(str);
    }

    if (is_char(str)) {
        if (str.size() == 3) {
          return str.at(1);
        }
        if (str.size() == 4) {
          switch (str.at(2)){
            case 'n': return '\n'; break;
            default: throw ParserException("Wrong char: " + str);
          }
        }
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
        return sign * stol(buffer, nullptr, 16);
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
        return sign * stol(buffer, nullptr, 2);
    }
    throw new ParserException("Wrong number: " + str);
};


bool Parser::is_binary_char(char c) {
    if (c != '0' && c != '1') {
        return false;
    }
    return true;
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

bool Parser::is_char(const std::string& str) {
    if (str.size() >= 3 && str.at(0) == '\'') {
        if (str.size() == 3 && str.at(2) == '\'') {
            return true;
        }
        if (str.size() == 4 && str.at(1) == '\\') {
            return true;
        }
    }
    return false;
}


bool Parser::is_number(const std::string& str) {
    return is_binary_number(str) || is_hex_number(str) || is_dec_number(str) || is_char(str);
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

std::vector<std::string> Parser::check_syntax(std::vector<std::string> args_tokens) {
    std::string error_message = "syntax error, comma problem: " + StringUtils::concat(" ",  args_tokens);
    if (args_tokens.size() != 0 && args_tokens[args_tokens.size() - 1] == ",") {
        throw ParserException(error_message);
    }
    std::vector<std::string> result;
    for (int i = 0; i < args_tokens.size(); i++) {
        if (i % 2 == 0) {
            result.push_back(args_tokens[i]);
        } else {
            if (args_tokens[i] != ",") {
                // can be double commma, missing comma
                throw ParserException(error_message);
            }
        }
    }
    return result;
}

std::vector<Instruction*> Parser::get_instructions() {
    std::vector<Instruction*> instruction_vector;
    Instruction* instruction;

    std::string instruction_token = lexer.get_next_token();
    while (instruction_token != "eof") {
        std::vector<std::string> args_tokens = check_syntax(lexer.get_tokens_until_end_line());
        try {
            instruction = get_instruction(instruction_token, args_tokens);
        } catch (const ParserException& e) {
            delete_instructions(instruction_vector);
            throw;
        } 
        instruction_vector.push_back(instruction);
        instruction_token = lexer.get_next_token();
    }
    return instruction_vector;
}

