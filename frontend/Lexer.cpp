#include "Lexer.hpp"



std::string Lexer::get_next_token() {
    if (eof_flag) { return "eof"; }
    std::string token = "";
    if (parsed_file.is_open()) {
        char ch;
        while (parsed_file) {
            if (str_buffer != "") {
                std::string ret = str_buffer;
                str_buffer = "";
                return ret;
            }
            ch = parsed_file.get();
            if (parsed_file.eof()) { 
                eof_flag = true;
                if (token != "") { return token; }  
                return "eof";
            }
            if (ch == ',' || ch == '\n' || ch == ' ') {
                if (ch != ' ') { str_buffer += ch; }   // need to return , or \n token to check syntax or stop
                if (token != "") { return token; }
                continue;
            }
            token += ch;
        }
        return token; 
    }
    return nullptr;  // if inner file error, idk what to do ;)
}


std::vector<std::string> Lexer::get_tokens_until_end_line() {
    std::vector<std::string> line;
    std::string token = get_next_token();
    while (token != "\n" && token != "eof") {
        line.push_back(token);
        token = get_next_token();
    }
    return line; 
}



