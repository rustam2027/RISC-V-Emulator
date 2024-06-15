#pragma once
#include <cassert>
#include <numeric>  //for accumulate
#include <string>
#include <vector>
#include <set>

#include "../Flags.hpp"
#include "../exceptions/ArgsParsingException.hpp"

struct StringUtils {
    static std::string concat(const std::string& sep, const std::vector<std::string>& strs) {
        assert(!strs.empty());
        return std::accumulate(std::next(strs.cbegin()), strs.cend(), *strs.cbegin(),
                               [&sep](std::string c, const std::string& s) { return std::move(c) + sep + s; });
    }

    static std::vector<std::string> split(const std::string& s, const char del) {
        std::vector<std::string> result;
        std::stringstream input(s);
        std::string item;

        while (getline(input, item, del)) {
            if (item.empty()) {
                continue;
            }
            result.push_back(item);
        }
        return result;
    }

    static std::set<FLAGS> parse_args(int argc, char* const args[]) {
        std::set<FLAGS> flags;

        for (int i = 2; i < argc; i++) {
            if (strcmp(args[i], "-g") == 0) {
                if (flags.contains(g)) {
                    throw ArgsParsingExceprion("Flag -g already used");
                }
                flags.insert(g);
            } else if (strcmp(args[i], "-d") == 0) {
                if (flags.contains(d)) {
                    throw ArgsParsingExceprion("Flag -d already used");
                }
                flags.insert(d);
            } else if (args[i][0] == '-') {
                throw ArgsParsingExceprion("Unsupported flag: " + std::string(args[i]));
            }
        }

        return flags;
    }
};
