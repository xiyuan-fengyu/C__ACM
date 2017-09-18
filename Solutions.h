//
// Created by xiyuan_fengyu on 2017/9/16.
//

#ifndef C_ACM_SOLUTIONS_H
#define C_ACM_SOLUTIONS_H

#include <iostream>
#include <vector>
#include <array>

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
        int base = 1;
        int flag = k == 0 ? 10 : 1;
        while (n / base >= flag) {
            int high = n / (base * 10);
            int ni = n / base % 10;
            if (ni > k) {
                count += (high + 1) * base;
            }
            else if (ni < k) {
                count += high * base;
            }
            else {
                count += high * base + n % base + 1;
            }

            base *= 10;
        }

        return count;
    }



    //时间复杂度不符合要求
//    int nthUglyNumber(int n) {
//        vector<int> uglyVec = {1, 2, 3, 4, 5, 6, 8, 9, 10};
//        if (n <= uglyVec.size()) return uglyVec[n - 1];
//
//        int index = 9;
//        int left = 1;
//        int right = 5;
//        while (index++ < n) {
//            int last = uglyVec[uglyVec.size() - 1];
//            int min = uglyVec[left] * uglyVec[right];
//
//            for (int r = right - 1, l = left + 1; l <= r; ) {
//                int temp = uglyVec[l] * uglyVec[r];
//                if (temp > last) {
//                    if (temp < min) {
//                        min = temp;
//                    }
//                    else if (temp >= min) {
//                        r--;
//                    }
//                }
//                else {
//                    l++;
//                }
//            }
//            uglyVec.push_back(min);
//
//            left = 1;
//            while (uglyVec[left] * uglyVec[++right] <= min);
//        }
//        return uglyVec[n - 1];
//    }


    int nthUglyNumber(int n) {
        vector<int> arr = vector<int>(n);
        arr[0] = 1;
        int index235[] = {0, 0, 0};
        int temp;
        int min;
        int minTypeIndex = 0;
        for (int i = 1; i < n; ) {
            min = arr[index235[0]] * 2;
            minTypeIndex = 0;

            if ((temp = arr[index235[1]] * 3) < min) {
                min = temp;
                minTypeIndex = 1;
            }

            if ((temp = arr[index235[2]] * 5) < min) {
                min = temp;
                minTypeIndex = 2;
            }

            if (min > arr[i - 1]) {
                arr[i] = min;
                i++;
            }
            index235[minTypeIndex]++;
        }
        return arr[n - 1];
    }



    int kthLargestElement(int n, vector<int> &nums) {
        return kthLargestElement(n, nums, 0, (int) nums.size() - 1);
    }

    int kthLargestElement(int n, vector<int> &nums, int left, int right) {
        if (left >= right) {
            return nums[left];
        }

        int l = left;
        int r = right;
        int key = nums[left];
        while (l < r) {
            while (l < r && nums[r] <= key) {
                r--;
            }
            nums[l] = nums[r];

            while (l < r && nums[l] >= key) {
                l++;
            }
            nums[r] = nums[l];
        }
        nums[l] = key;

        if (l == n - 1) {
            return key;
        }
        else if (l < n - 1) {
            return kthLargestElement(n, nums, l + 1, right);
        }
        else return kthLargestElement(n, nums, left, l - 1);
    }


    void test() {

        vector<int> arr = {
                9,3,2,4,8
        };
        cout << kthLargestElement(3, arr) << endl;

//        cout << nthUglyNumber(1665) << endl;

//        cout << digitCounts(1, 10) << endl;

//        cout << trailingZeros(10) << endl;

//        cout << aplusb(2, 2) << endl;

    }

};


#endif //C_ACM_SOLUTIONS_H
