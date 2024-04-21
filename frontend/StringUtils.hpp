#pragma once
#include <cassert>
#include <numeric>   //for accumulate
#include <string>
#include <vector>


struct StringUtils {
    static std::string concat(const std::string& sep, const std::vector<std::string>& strs) {
        assert(!strs.empty());
        return std::accumulate(std::next(strs.cbegin()), strs.cend(), *strs.cbegin(),
            [&sep](std::string c, const std::string& s)
                { return std::move(c) + sep + s; });
    }

    static std::vector<std::string> split(const std::string& s, const char del) {
        std::vector<std::string> result;
        std::stringstream input(s);
        std::string item;

        while (getline (input, item, del)) {
            if (item.empty()) { continue; } 
            result.push_back(item);
        }
        return result;
    }
};