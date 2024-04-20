#include "Preprocessor.hpp"


void Preprocessor::string_replace(std::string& input, const std::string& src, const std::string& dst) {
    size_t pos = input.find(src);
    while(pos != std::string::npos) {
        input.replace(pos, src.size(), dst);
        pos = input.find(src, pos);
    }
}


std::vector<std::string> Preprocessor::split_and_delete_comments(const std::string& s) {
    std::vector<std::string> result;
    std::stringstream input(s);
    std::string item;

    while (getline (input, item, ' ')) {
        if (item.empty() || item[0] == '\t') { continue; }         // unused space
        if (item[0] == '#') { return result; }                     // comment start
        result.push_back(item);
    }
    return result;
}


void Preprocessor::delete_commas(std::vector<std::string>& line) {
    for (std::string& word: line) { string_replace(word, ",", ""); }
}


void Preprocessor::replace_eqv(std::string& str) {
    for(auto& pair : eqv) {
        string_replace(str, pair.first, pair.second);
    }
}


std::string Preprocessor::concat(const std::string& sep, const std::vector<std::string>& strs) {
    assert(!strs.empty());

    return std::accumulate(std::next(strs.cbegin()), strs.cend(), *strs.cbegin(),
        [&sep](string c, const string& s)
            { return std::move(c) + sep + s; });
}


void Preprocessor::preprocess() {
    std::ifstream in(file);
    std::ofstream out;
    out.open("_in.parse"); 
    int counter = 0;  // counter for lines in _in.parse
    if (in.is_open()) {
        std::string current_line;
        while (getline(in, current_line)) { 
            if (current_line.empty() || current_line[0] == '#') {
                continue;
            }
            std::vector<std::string> buf = split_and_delete_comments(current_line);
            if (buf.empty()) { continue; }
            std::string first = buf.front();
            if (macro.find(first) != macro.end()) {
                delete_commas(buf);
                buf.erase(buf.begin());
                if (macro[first].params.size() != buf.size()) {
                     throw PreprocessorException("invalid args amount for macro: " + first);
                }
                for (std::string line: macro[first].macro_lines) {
                    for (size_t i = 0; i < macro[first].params.size(); i++) {
                        string_replace(line, macro[first].params[i], buf[i]);
                    }
                    counter++;
                    replace_eqv(line);
                    out << line << endl; 
                }
                continue;
            }
            if (first.at(0) == '.') {
                switch(mapping_macro[first]) {
                    case 0: {  // .macro
                      Macro m_data;
                      std::string name = buf[1];
                      delete_commas(buf);
                      buf.erase(buf.begin(), buf.begin() + 2);                      // delete .macro and macro_name
                      m_data.params = buf;                                          // many parameters
                      while (getline(in, current_line)) {
                        std::vector<std::string> in_buf = split_and_delete_comments(current_line);  // delete comments
                        if (in_buf.front() == ".end_macro") { break; }
                        m_data.macro_lines.push_back(concat(" ", in_buf)); 
                      }
                      macro[name] = m_data;
                      break;
                    }
                    case 1:  {   // .eqv
                      if (buf.size() == 3) {
                        eqv[buf[1]] = buf[2];    // name : string to replace
                      } else {
                        throw PreprocessorException("invalid definition: " + concat(" ", buf));
                      } 
                      break;
                    }
                    default:
                        // can be .text .section .data .bss 
                       continue;
                }
                continue;
            }
            int last = first.size() - 1;
            if (buf.front()[last] == ':') {
                if (buf.size() == 1) {
                    first.erase(last, 1);
                    labels[first] = counter;
                    continue; 
                }
                out.close();
                in.close();
                throw PreprocessorException("invalid label name: " + concat(" ", buf));
            }
            counter++;
            current_line = concat(" ", buf);
            replace_eqv(current_line);
            out << current_line << endl;             
        }
    }
    out.close();
    in.close();
}