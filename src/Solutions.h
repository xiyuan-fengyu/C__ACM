//
// Created by xiyuan_fengyu on 2018/1/5.
//

#ifndef C_ACM_SOLUTIONS_H
#define C_ACM_SOLUTIONS_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include <climits>
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
        int size1 = static_cast<int>(nums1.size());
        int size2 = static_cast<int>(nums2.size());
        if (size1 > size2) return findMedianSortedArrays(nums2, nums1);

        int left = 0;
        int right = size1;
        while (true) {
            int i = (left + right) / 2;
            int j = (size1 + size2) / 2 - i;
            int leftMax = max(i > 0 ? nums1[i - 1] : INT_MIN, j > 0 ? nums2[j - 1] : INT_MIN);
            int rightMin = min(i < size1 ? nums1[i] : INT_MAX, j < size2 ? nums2[j] : INT_MAX);
            if (leftMax <= rightMin) {
                return (size1 + size2) % 2 ? rightMin : (leftMax + rightMin) / 2.0;
            }
            else {
                if (i < size1 && nums1[i] == rightMin) left = i + 1;
                else right = i - 1;
            }
        }
    }



    string longestPalindrome(string s) {
        int len = s.size();
        if (len <= 1) return s;

        int left, right, maxLeft, tempMax, resMax = 0;
        for (int i = 0; i < len - 1; ++i) {
            if (s[i] == s[i + 1]) {
                left = i - 1;
                right = i + 2;
                tempMax = 2;
                while (left >= 0 && right < len) {
                    if (s[left] == s[right]) {
                        left--;
                        right++;
                        tempMax += 2;
                    }
                    else break;
                }
                if (resMax < tempMax) {
                    resMax = tempMax;
                    maxLeft = left + 1;
                }
            }

            left = i - 1;
            right = i + 1;
            tempMax = 1;
            while (left >= 0 && right < len) {
                if (s[left] == s[right]) {
                    left--;
                    right++;
                    tempMax += 2;
                }
                else break;
            }

            if (resMax < tempMax) {
                resMax = tempMax;
                maxLeft = left + 1;
            }
        }
        return s.substr(maxLeft, resMax);
    }



    string longestPalindromeManacher(string s) {
        int len = s.size();
        if (len <= 1) return s;

        // 不用构造 #0#1#0#这种字符串，而且可以跳过#这种位置的相等校验(通过设置 left, right的初始值，变化量为2)
        len = len * 2 + 1;
        int cache[len];
        int pos = -1;
        int maxR = -1;
        int maxPos = -1;
        int maxLen = -1;
        int left, right;

        for (int i = 0; i < len; ++i) {
            if (i > maxR) {
                left = i % 2 ? i - 2 : i - 1;
                right = 2 * i - left;
                while (left >= 0 && right < len) {
                    if (s[left / 2] == s[right / 2]) {
                        left -= 2;
                        right += 2;
                    }
                    else break;
                }
                pos = i;
                maxR = right - 1;
                cache[i] = right - i;

                if (maxLen < cache[i] - 1) {
                    maxLen = cache[i] - 1;
                    maxPos = i;
                }
            }
            else {
                int rI = cache[pos * 2 - i];
                if (rI < maxR - i + 1) cache[i] = rI;
                else {
                    right = (maxR + 1) % 2 ? maxR + 1 : maxR + 2;
                    left = i * 2 - right;
                    while (left >= 0 && right < len) {
                        if (s[left / 2] == s[right / 2]) {
                            left -= 2;
                            right += 2;
                        }
                        else break;
                    }
                    pos = i;
                    maxR = right - 1;
                    cache[i] = right - i;

                    if (maxLen < cache[i] - 1) {
                        maxLen = cache[i] - 1;
                        maxPos = i;
                    }
                }
            }
        }

        return s.substr((maxPos - 1) / 2 - cache[maxPos] / 2 + 1, cache[maxPos] - 1);
    }


    string convert(const string &s, int numRows) {
        if (s.length() <= numRows || numRows < 2) return s;

        int len = s.length();
        int col, modCol, sIndex;
        stringstream ss;
        for (int i = 0; i < numRows; ++i) {
            col = 0;
            while (true) {
                modCol = col % (numRows - 1);
                sIndex = col / (numRows - 1) * (numRows * 2 - 2) + (modCol == 0 ? i : numRows + modCol - 1);
                if (sIndex >= len) break;
                ss << s[sIndex];
                if (modCol == 0) col += i + 1 == numRows ? numRows - 1 : numRows - i - 1;
                else col += numRows - 1 - modCol;
            }
        }
        return ss.str();
    }

    string zigzag(const string &s, int numRows) {
        int len = s.length();
        int col, modCol, sIndex;
        stringstream ss;
        for (int i = 0; i < numRows; ++i) {
            col = 0;
            while (true) {
                modCol = col % (numRows - 1);
                if (modCol == 0 || modCol + i + 1 == numRows) {
                    sIndex = col / (numRows - 1) * (numRows * 2 - 2) + (modCol == 0 ? i : numRows + modCol - 1);
                    if (sIndex >= len) {
                        ss << '\n';
                        break;
                    }
                    ss << s[sIndex];
                }
                else ss << ' ';
                col++;
            }
        }
        return ss.str();
    }



    int reverse(int x) {
        long res = 0;
        while (x) {
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res > INT_MAX || res < INT_MIN ? 0 : res;
    }



    int myAtoi(const string& str) {
        long res = 0;
        int np = 0;
        for (char i : str) {
            if (np) {
                if (i >= '0' && i <= '9') {
                    res = res * 10 + int(i - '0');
                    if (np == 1 && res > INT_MAX) return INT_MAX;
                    else if (np == -1 && -res < INT_MIN) return INT_MIN;
                }
                else break;
            }
            else {
                if (i == '-') np = -1;
                else if (i == '+') np = 1;
                else if (i >= '0' && i <= '9') {
                    np = 1;
                    res = int(i - '0');
                }
                else if (i != ' ') return 0;
            }
        }
        return int(res * np);
    }


    bool isPalindrome(int x) {
        if (x < 0) return false;

        int l = x, r = x, tenL = 1, tenR = 10;
        while (l) {
            if (l > 9) tenL *= 10;
            l /= 10;
        }

        l = x;
        while (tenL >= tenR) {
            if (l / tenL != r % 10) return false;
            l %= tenL;
            tenL /= 10;
            r /= 10;
            tenR *= 10;
        }
        return true;
    }


    void test() {

        cout << isPalindrome(2147447412) << endl;


//        cout << myAtoi("123456") << endl;
//        cout << myAtoi("-123456") << endl;
//        cout << myAtoi(" -123456s") << endl;


//        cout << reverse(120) << endl;
//        cout << reverse(-120) << endl;
//        cout << reverse(1534236469) << endl;


//        cout << convert("PAYPALISHIRING", 3) << endl;
//        cout << zigzag("PAYPALISHIRING", 3) << endl;
//        cout << convert("abcdefghijklmnopqrstuvwxyz", 4) << endl;
//        cout << zigzag("abcdefghijklmnopqrstuvwxyz", 4) << endl;

        
//        cout << longestPalindromeManacher("cccaacc") << endl;
//        cout << longestPalindrome("abaabc") << endl;


//        vector<int> nums1 {1, 3};
//        vector<int> nums2 {2};
//        cout << findMedianSortedArrays(nums1, nums2) << endl;


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
