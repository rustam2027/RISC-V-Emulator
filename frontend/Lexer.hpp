#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "../exceptions/ParserException.hpp"

class Lexer {
    std::stringstream& inparse; 
    std::string str_buffer;
    bool eof_flag;

  public:
    Lexer(std::stringstream& inparse_): inparse(inparse_) {}
    ~Lexer()=default;

    std::string get_next_token();
    std::vector<std::string> get_tokens_until_end_line();

};