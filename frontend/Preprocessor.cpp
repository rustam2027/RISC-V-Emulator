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


void Preprocessor::replace(std::string& str, std::map<std::string, std::string> replace_map) {
    for(auto& pair : replace_map) {
        string_replace(str, pair.first, pair.second);
    }
}

bool Preprocessor::is_label(std::string& token) {
    return token[token.size() - 1] == ':';
}

void Preprocessor::add_label(std::string& label, int lines_counter) {
    label.erase(label.size() - 1, 1);
    labels[label] = lines_counter;
}

std::map<std::string, std::string> Preprocessor::create_replace_labels(std::vector<std::string>& macro_labels, std::string num, std::string name) {
    std::map<std::string, std::string> replace_labels;
    for (std::string label: macro_labels) {
        label.erase(label.size() - 1, 1);
        replace_labels[label] = name + "_" + num + "_" + label;
    }
    return replace_labels;
}

void Preprocessor::inline_macros(std::vector<std::string>& input_line, int& counter_in_parse, bool write_to_file, Macros* m_data) {
    std::string first = input_line.front();
    int num = macros[first].instances++;         // get number to create custom label name 
    std::map<std::string, std::string> replace_labels = create_replace_labels(macros[first].macros_labels, std::to_string(num), first);
    delete_commas(input_line);
    input_line.erase(input_line.begin());
    if (macros[first].params.size() != input_line.size()) {
        close_resources();
        throw PreprocessorException("invalid args amount for macro: " + first);
    }

    for (size_t j = 0; j < macros[first].macros_lines.size(); j++) {
        std::string line = macros[first].macros_lines[j];
        if (is_label(line)) {
            line = first + "_" + std::to_string(num) + "_" + line;
            if (write_to_file) {
              add_label(line, counter_in_parse);
            } else {
              m_data->macros_lines.push_back(line);
            }
            continue;
        }
        for (size_t i = 0; i < macros[first].params.size(); i++) {
            string_replace(line, macros[first].params[i], input_line[i]);
        }
        replace(line, eqv);

        std::vector<std::string> buffer = StringUtils::split(line, ' ');
        if (buffer.size() > 1) {
            int last = buffer.size() - 1;
            if (replace_labels.find(buffer[last]) !=  replace_labels.end()) {
                buffer[last] = replace_labels[buffer[last]];
            }
        }
        line = StringUtils::concat(" ", buffer);

        if (write_to_file) {
          counter_in_parse++;
          from_inparse_to_in.push_back(macros[first].start_line + j);
          out << line << std::endl; 
        } else {
          m_data->macros_lines.push_back(line);  
        }
    }
}


std::vector<std::string> Preprocessor::all_lines_in() {
    assert(debug_mode == true);

    in.open(file);
    std::vector<std::string> result;
    std::string current_line;
    while (getline(in, current_line)) { result.push_back(current_line); }
    in.close();
    return result;
}


void Preprocessor::close_resources() { 
    out.close(); 
    in.close();
}



/* from_in_to_inparse */

/* 
empty line or comment                  -> -1  
. definition (.macro .eqv .text .data) -> -2
label                                  -> -3
 */



void Preprocessor::preprocess() {
    in.open(file);
    out.open("_in.parse"); 
    int counter_in_parse = 0;        // counter for lines in _in.parse
    int counter_in = -1;             // counter for lines in in.txt

    if (in.is_open()) {
        std::string current_line;
        while (getline(in, current_line)) { 
            counter_in++;
            if (current_line.empty() || current_line[0] == '#') {
                from_in_to_inparse.push_back(-1);                  // comment or empty line -> -1 
                continue;
            }
            std::vector<std::string> buf = split_and_delete_comments(current_line);
            if (buf.empty()) { 
                from_in_to_inparse.push_back(-1); 
                continue; 
            }
            std::string first = buf.front();
            if (macros.find(first) != macros.end()) {
                from_in_to_inparse.push_back(counter_in_parse);    // pointer to start of the macros
                inline_macros(buf, counter_in_parse, true, nullptr);
                continue;
            }
            if (first.at(0) == '.') {  
                from_in_to_inparse.push_back(-2); 
                if (first == ".macro") {
                    Macros m_data;
                    m_data.start_line = counter_in + 1;
                    std::string name = buf[1];
                    delete_commas(buf);
                    buf.erase(buf.begin(), buf.begin() + 2);                      // delete .macro and macro_name
                    m_data.params = buf;                                          // many parameters
                    std::vector<std::string> macros_labels;
                    while (getline(in, current_line)) {
                      counter_in++;
                      from_in_to_inparse.push_back(-2); 
                      std::vector<std::string> in_buf = split_and_delete_comments(current_line);  // delete comments
                      if (in_buf.empty()) { continue; }
                      if (in_buf.front() == ".end_macro") { break; }
                      if (in_buf.size() == 1 && is_label(in_buf.front())) {
                        m_data.macros_labels.push_back(in_buf.front());
                        m_data.macros_lines.push_back(in_buf.front());  
                        continue;
                      }
                      if (macros.find(in_buf.front()) != macros.end()) {
                        inline_macros(in_buf, counter_in_parse, false, &m_data);
                        continue;
                      }
                      m_data.macros_lines.push_back(StringUtils::concat(" ", in_buf)); 
                    }
                    macros[name] = m_data;
                } else if (first == ".eqv") {
                    if (buf.size() == 3) {
                        eqv[buf[1]] = buf[2];    // name : string to replace
                    } else {
                        close_resources();
                        throw PreprocessorException("invalid definition: " + StringUtils::concat(" ", buf));
                    } 
                } else if (first == ".data" || first == ".text") {
                    // do something 
                } else {
                    close_resources();
                    throw PreprocessorException("not supported: " + first);
                }     
                continue;
            }

            if (buf.size() == 1 && is_label(first)) {
                add_label(first, counter_in_parse);
                from_in_to_inparse.push_back(-3);   
                continue;
            }

            from_in_to_inparse.push_back(counter_in_parse); 
            from_inparse_to_in.push_back(counter_in);
            counter_in_parse++;

            current_line = StringUtils::concat(" ", buf);
            replace(current_line, eqv);
            out << current_line << std::endl;         
        }
    }
    close_resources();
}