#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "../exceptions/PreprocessorException.hpp"
#include "Parser.hpp"



class Preprocessor {
    bool debug_mode;
    std::string file;

    struct Macro {
      std::vector<std::string> params;
      std::vector<std::string> macro_lines;
    };

    std::map<std::string, int> labels;
    std::map<std::string, std::string> eqv;

    std::map<std::string, Macro> macro;
    std::map <std::string, int> mapping_macro = {{".macro", 0}, {".eqv", 1}};


    // if debug --> create two arrays 

    void string_replace(std::string& input, const std::string& src, const std::string& dst);
    void delete_commas(std::vector<std::string>& line);
    void replace_eqv(std::string& str);

    std::vector<std::string> split_and_delete_comments(const std::string& s);
    string concat(const std::string& sep, const std::vector<std::string>& strs);

  public:
    Preprocessor(bool debug, std::string file): debug_mode(debug), file(file)  {}
    void preprocess(); 
    map<std::string, int> get_labels() { return labels; }  // make it better

};