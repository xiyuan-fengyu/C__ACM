//
// Created by xiyuan_fengyu on 2018/1/5.
//

#ifndef C_ACM_OPERATORS_H
#define C_ACM_OPERATORS_H

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<T>& vec) {
    for (long i = 0, size = vec.size(); i < size; ++i) {
        os << vec[i];
        if (i + 1 < size) {
            os << ", ";
        }
    }
    return os;
}


#endif //C_ACM_OPERATORS_H
