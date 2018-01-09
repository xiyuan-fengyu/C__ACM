//
// Created by xiyuan_fengyu on 2018/1/5.
//

#ifndef C_ACM_OPERATORS_H
#define C_ACM_OPERATORS_H

#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<T>& vec) {
//    for (long i = 0, size = vec.size(); i < size; ++i) {
//        os << vec[i];
//        if (i + 1 < size) {
//            os << ", ";
//        }
//    }
    if (!vec.empty()) {
        copy(vec.begin(), --vec.end(), ostream_iterator<T>(os, ", "));
        os << vec.back();
    }
    return os;
}


#endif //C_ACM_OPERATORS_H
