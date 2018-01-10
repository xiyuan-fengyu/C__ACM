//
// Created by xiyuan_fengyu on 2018/1/10.
//

#ifndef C_ACM_UTIL_H
#define C_ACM_UTIL_H

#include <vector>
#include <iostream>
#include <iterator>
#include <sstream>

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

std::vector<std::string> split(const std::string &text, const std::string &delimiters = " ");

#endif //C_ACM_UTIL_H
