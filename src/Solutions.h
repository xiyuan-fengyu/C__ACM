//
// Created by xiyuan_fengyu on 2018/1/5.
//

#ifndef C_ACM_SOLUTIONS_H
#define C_ACM_SOLUTIONS_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include "operators.h"


using namespace std;

class Solutions {
public:

    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res {-1, -1};
        unordered_map<int, int> cache;
        int size = static_cast<int>(nums.size());
        int cur;
        int other;
        for (int i = 0; i < size; ++i) {
            cur = nums[i];
            other = target - cur;
            int otherIndex = cache[other] - 1;
            if (otherIndex > -1) {
                res[0] = otherIndex;
                res[1] = i;
                return res;
            }
            else {
                cache[cur] = i + 1;
            }
        }
        return res;
    }

    void test() {

        int target = -8;
        vector<int> nums {-1,-2,-3,-4,-5};
        cout << twoSum(nums, target) << endl;

    }

};


#endif //C_ACM_SOLUTIONS_H
