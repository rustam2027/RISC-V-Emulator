#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "../exceptions/ParserException.hpp"

class Lexer {
    std::ifstream parsed_file; 
    std::string str_buffer;
    bool eof_flag;
    bool bracket_flag;

  public:
    Lexer() { parsed_file.open("_in.parse"); }
    ~Lexer() { parsed_file.close(); }

    std::string get_next_token();
    std::vector<std::string> get_tokens_until_end_line();

};