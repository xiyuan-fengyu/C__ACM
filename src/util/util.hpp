//
// Created by xiyuan_fengyu on 2018/1/10.
//

#ifndef C_ACM_UTIL_H
#define C_ACM_UTIL_H

#include <vector>
#include <iostream>
#include <iterator>
#include <sstream>

namespace xiyuan {

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
//    for (long i = 0, size = vec.size(); i < size; ++i) {
//        os << vec[i];
//        if (i + 1 < size) {
//            os << ", ";
//        }
//    }
        if (!vec.empty()) {
            std::copy(vec.begin(), --vec.end(), std::ostream_iterator<T>(os, ", "));
            os << vec.back();
        }
        return os;
    }

    std::vector<std::string> split(const std::string &text, const std::string &delimiters = " ") {
        std::vector<std::string> tokens;
        std::size_t start = 0, end = 0, delLen = delimiters.length();
        while ((end = text.find(delimiters, start)) != std::string::npos) {
            tokens.push_back(text.substr(start, end - start));
            start = end + delLen;
        }
        tokens.push_back(text.substr(start));
        return tokens;
    }

}

#endif //C_ACM_UTIL_H
