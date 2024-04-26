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
      int instances = 0;
      int start_line = 0;
      std::vector<std::string> params;
      std::vector<std::string> macros_lines;
      std::vector<std::string> macros_labels;
    };

    std::map<std::string, int> labels;
    std::map<std::string, std::string> eqv;

    std::map<std::string, Macros> macros;

    std::vector<int> from_in_to_inparse;  
    std::vector<int> from_inparse_to_in;

    void string_replace(std::string& input, const std::string& src, const std::string& dst);
    void delete_commas(std::vector<std::string>& line);
    void replace(std::string& str, std::map<std::string, std::string> replace_map);

    std::vector<std::string> split_and_delete_comments(const std::string& s);
    bool is_label(std::string& token);
    void add_label(std::string& label, int lines_counter);
    void inline_macros(std::vector<std::string>& input_line, int& counter_in_parse, bool write_to_file, Macros* m_data);
    std::map<std::string, std::string> create_replace_labels(std::vector<std::string>& macro_labels, std::string num, std::string name);

  public:
    Preprocessor(bool debug, std::string file): debug_mode(debug), file(file)  {}
    void preprocess(); 
    std::map<std::string, int> get_labels() { return labels; } 
    std::vector<int> get_from_in_to_inparse() { return from_in_to_inparse; }
    std::vector<int> get_from_inparse_to_in() { return from_inparse_to_in; }

    std::vector<std::string> all_lines_in();
};