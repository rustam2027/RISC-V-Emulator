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
    std::string file;
    std::ifstream in;

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
    std::vector<std::string> all_lines;
    std::stringstream inparse;

    static void string_replace(std::string& input, const std::string& src, const std::string& dst);
    static void delete_commas(std::vector<std::string>& line);
    static void replace(std::string& str, std::map<std::string, std::string> replace_map);

    static std::vector<std::string> split_and_delete_comments(const std::string& s);
    static bool is_label(std::string& token);
    void add_label(std::string& label, int lines_counter);
    void inline_macros(std::vector<std::string>& input_line, int& counter_in_parse, bool write_to_file, Macros* m_data);
    std::map<std::string, std::string> create_replace_labels(std::vector<std::string>& macro_labels, std::string num, std::string name);

  public:
    Preprocessor(bool debug, std::string file): file(file)  {
      in.open(file);
      std::string current_line;
      while (getline(in, current_line)) { all_lines.push_back(current_line); }
      in.close();
    }

    std::map<std::string, int>& get_labels() { return labels; } 
    std::vector<int>& get_from_in_to_inparse() { return from_in_to_inparse; }
    std::vector<int>& get_from_inparse_to_in() { return from_inparse_to_in; }
    std::stringstream& get_inparse() { return inparse; };
    std::vector<std::string>& all_lines_in() { return all_lines; }
    void preprocess();
    void dump_inparse();
};
