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
    std::map<std::string, Macro> macro;
    // if debug --> create two arrays 

    void string_replace(std::string& input, const std::string& src, const std::string& dst);

    std::vector<std::string> split_and_delete_comments(const std::string& s, bool remove_comma);
    string concat(const std::string& sep, const std::vector<std::string>& strs);

  public:
    Preprocessor(bool debug, std::string file): debug_mode(debug), file(file)  {}
    void preprocess();   // make in better
    map<std::string, int> get_labels() { return labels; }  // make it better

};