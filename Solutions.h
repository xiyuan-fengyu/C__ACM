//
// Created by xiyuan_fengyu on 2017/9/16.
//

#ifndef C_ACM_SOLUTIONS_H
#define C_ACM_SOLUTIONS_H

#include <iostream>

using namespace std;

class Solutions {

public:

    int aplusb(int a, int b) {
        if (b == 0) {
            return a;
        }
        return aplusb(a ^ b, (a & b) << 1);
    }

    void test() {

//        cout << aplusb(2, 2) << endl;

    }

};


#endif //C_ACM_SOLUTIONS_H
