//
// Created by xiyuan_fengyu on 2018/1/5.
//

#ifndef C_ACM_SOLUTIONS_H
#define C_ACM_SOLUTIONS_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include "util/util.h"
#include "model/ListNode.h"


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



    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode tempHead(0), *cur = &tempHead;
        while ((tempHead.val /= 10) || l1 || l2) {
            if (l1) tempHead.val += l1->val, l1 = l1->next;
            if (l2) tempHead.val += l2->val, l2 = l2->next;
            cur = (cur->next = new ListNode(tempHead.val % 10));
        }
        return tempHead.next;
    }



    int lengthOfLongestSubstring(string s) {
        if (s.empty()) return 0;

        int max = 0;
        int charIndexes[128] {};
        charIndexes[int(s[0])] = 1;
        int i = 1, j = 0, len = static_cast<int>(s.length());
        for ( ; i < len; ++i) {
            char c = s[i];
            int &lastI = charIndexes[int(s[i])];
            if (lastI > 0) {
                if (max < i - j) max = i - j;
                if (lastI > j) j = lastI;
            }
            lastI = i + 1;
        }
        if (max < i - j) max = i - j;
        return max;
    }



    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int i = -1;
        int j = -1;
        int index = -1;
        int size1 = static_cast<int>(nums1.size());
        int size2 = static_cast<int>(nums2.size());
        int mid = (size1 + size2) / 2;
        int midLeft = (size1 + size2) % 2 == 0 ? mid - 1 : -1;
        int midLeftVal = 0;
        int ij;
        while (i + 1 < size1 || j + 1 < size2) {
            if (i + 1 < size1) {
                if (j + 1 < size2) {
                    if (nums1[i + 1] <= nums2[j + 1]) {
                        i++;
                        ij = 0;
                    }
                    else {
                        j++;
                        ij = 1;
                    }
                }
                else {
                    i++;
                    ij = 0;
                }
            }
            else {
                j++;
                ij = 1;
            }
            index++;

            if (midLeft > -1 && index == midLeft) {
                midLeftVal = ij ? nums2[j] : nums1[i];
            }
            if (index == mid) {
                int temp = ij ? nums2[j] : nums1[i];
                return midLeft > -1 ? (midLeftVal + temp) / 2.0 : temp;
            }
        }
        return 0;
    }

    void test() {

        vector<int> nums1 {1, 3};
        vector<int> nums2 {2, 4};
        cout << findMedianSortedArrays(nums1, nums2) << endl;


//        cout << lengthOfLongestSubstring("abcabcbb") << endl;


//        ListNode* listNode1 = ListNode::parse("2 -> 4 -> 3");
//        ListNode* listNode2 = ListNode::parse("5 -> 6 -> 4");
//        cout << *addTwoNumbers(listNode1, listNode2) << endl;


//        int target = -8;
//        vector<int> nums {-1,-2,-3,-4,-5};
//        cout << twoSum(nums, target) << endl;


    }

};


#endif //C_ACM_SOLUTIONS_H
