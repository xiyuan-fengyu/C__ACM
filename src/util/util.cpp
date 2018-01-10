//
// Created by xiyuan_fengyu on 2018/1/10.
//

#include "util.h"

std::vector<std::string> split(const std::string &text, const std::string &delimiters) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0, delLen = delimiters.length();
    while ((end = text.find(delimiters, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + delLen;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}