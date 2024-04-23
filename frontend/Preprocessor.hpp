#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "../exceptions/PreprocessorException.hpp"
#include "StringUtils.hpp"



class Preprocessor {
    bool debug_mode;
    std::string file;
    std::ifstream in;
    std::ofstream out;
    void close_resources();

    struct Macros {
      std::vector<std::string> params;
      std::vector<std::string> macros_lines;
    };

    std::map<std::string, int> labels;
    std::map<std::string, std::string> eqv;

    std::map<std::string, Macros> macros;

    // if debug --> create two arrays  

    void string_replace(std::string& input, const std::string& src, const std::string& dst);
    void delete_commas(std::vector<std::string>& line);
    void replace_eqv(std::string& str);

    std::vector<std::string> split_and_delete_comments(const std::string& s);

  public:
    Preprocessor(bool debug, std::string file): debug_mode(debug), file(file)  {}
    void preprocess(); 
    std::map<std::string, int> get_labels() { return labels; } 

};