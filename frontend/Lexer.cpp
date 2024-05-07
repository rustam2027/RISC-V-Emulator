#include "Lexer.hpp"



std::string Lexer::get_next_token() {
    if (eof_flag) { return "eof"; }
    std::string token = "";
    char ch;
    while (inparse) {
        if (str_buffer != "") {
            std::string ret = str_buffer;
            str_buffer = "";
            return ret;
        }
        ch = inparse.get();
        if (inparse.eof()) { 
            eof_flag = true;
            if (token != "") { return token; }  
            return "eof";
        }
        if (ch == ',' || ch == '\n' || ch == ' ' || ch == '\t') {
            if (ch != ' ' && ch != '\t') { str_buffer += ch; }   // need to return , or \n token to check syntax or stop
            if (token != "") { return token; }
            continue;
        }
        token += ch;
    }
    return token; 
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



