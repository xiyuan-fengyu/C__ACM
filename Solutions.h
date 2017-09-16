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



    long long trailingZeros(long long n) {
        if (n < 5) return 0;

        long long m = n / 5;
        return m + trailingZeros(m);
    }



    int digitCounts(int k, int n) {
        if (n < 10) return k <= n ? 1 : 0;

        int count = 0;
        int nine = 9;
        int index = 1;
        while (true) {
            int ten = (nine + 1) / 10;
            if (n >= nine) {
                if (k == 0) {
                    count += index == 1 ? 1 : (index - 1) * ten * nine;
                }
                else {
                    count += index * ten;
                }
            }
            else {
                int highNum = n / ten;
                int lowNum = n - highNum * ten;
                //高位出现 k 的次数
                if (highNum == k) {
                    count +=lowNum + 1;
                }
                else if (highNum > k && k != 0) {
                    count += ten;
                }

                //低位出现 k 的次数
                // n ~ [highNum]0000 这种数字低位出现 k 的次数
                if (k != 0) {
                    count += digitCounts(k, lowNum);
                }
                else {
                    //todo

                }

                if (highNum > 1) {
                    // [highNum-1]9999 ~ 10000 这种数字低位出现 k 的次数
                    count += (highNum - 1) * ten / 100 * (index - 1);
                }

                break;
            }
            nine = nine * 10 + 9;
            index++;
        }
        return count;
    }



    void test() {


        cout << digitCounts(1, 10) << endl;

//        cout << trailingZeros(10) << endl;


//        cout << aplusb(2, 2) << endl;

    }

};


#endif //C_ACM_SOLUTIONS_H
