//
// Created by xiyuan_fengyu on 2018/1/5.
//

#ifndef C_ACM_SOLUTIONS_H
#define C_ACM_SOLUTIONS_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <climits>
#include "util/util.hpp"
#include "model/ListNode.hpp"
#include <algorithm>
#include <stack>
#include <random>

using namespace std;
using namespace xiyuan;

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



    bool isMatch(const string &s, const string &p) {
        auto sLen = int(s.length());
        auto pLen = int(p.length());
        bool cache[sLen + 1][pLen + 1] {};
        cache[sLen][pLen] = true;
        bool firstMatch;
        for (int i = sLen; i >= 0; --i) {
            for (int j = pLen - 1; j >= 0; --j) {
                firstMatch = i < sLen && (p[j] == s[i] || p[j] == '.');
                if (j + 1 < pLen && p[j + 1] == '*') {
                    cache[i][j] = cache[i][j + 2] || (firstMatch && cache[i + 1][j]);
                }
                else {
                    cache[i][j] = firstMatch && cache[i + 1][j + 1];
                }
            }
        }
        return cache[0][0];
    }


    // 266ms
    int maxAreaV1(vector<int>& height) {
        int maxA = 0;
        int size = static_cast<int>(height.size());
        for (int i = size - 1, j, tempA, tempH; i > 0; --i) {
            j = 0;
            tempH = height[i];
            while (j < i && maxA / (i - j) < tempH) {
                tempA = min(height[j], tempH) * (i - j);
                if (tempA > maxA) maxA = tempA;
                j++;
            }
        }
        return maxA;
    }

    // 27 ms
    int maxAreaV2(vector<int>& height) {
        int maxA = 0;

        // 找到拱形的数据变化 或者 一直递增的数据变化，并记录其index， 例如：
        // 1, 2, 3, 4, 2, 1
        // 1, 3, 5, 6
        vector<tuple<int, int>> indexedHeight;
        int lastMaxH = -1, lastMaxIndex = 0, h;
        for (int i = 0, size = int(height.size()); i < size; ++i) {
            h = height[i];
            while (!indexedHeight.empty()) {
                auto temp = indexedHeight.back();
                if (get<0>(temp) == lastMaxIndex) break;
                if (get<1>(temp) <= h) indexedHeight.pop_back();
                else break;
            }
            if (h > lastMaxH) {
                lastMaxH = h;
                lastMaxIndex = i;
            }
            indexedHeight.push_back(make_tuple(i, h));
        }

        // 左右两端各一个指针， 当两端 一样高时，都像中靠拢一步，否则较矮的指针向中靠一步
        int i = 0, j = int(indexedHeight.size() - 1), leftH, rightH;
        tuple<int, int> left, right;
        while (i < j) {
            left = indexedHeight[i];
            right = indexedHeight[j];
            leftH = get<1>(left);
            rightH = get<1>(right);
            maxA = max(maxA, min(leftH, rightH) * (get<0>(right) - get<0>(left)));
            if (leftH == rightH) {
                i++;
                j--;
            }
            else if (leftH < rightH) i++;
            else j--;
        }
        return maxA;
    }

    // 20ms
    int maxArea(vector<int>& height) {
        int maxA = 0;
        // 左右两端各一个指针， 分别记录两端遇到的最大值，每当有一端最大值更新时，
        // 就计算一次最大值，当两端 最大值一样高时，都像中靠拢一直到找到更高的，否则较矮的指针向中靠拢
        int i = 0, j = int(height.size() - 1), leftMaxH, rightMaxH, tempMax;
        while (i < j) {
            leftMaxH = height[i];
            rightMaxH = height[j];
            tempMax = (leftMaxH < rightMaxH ? leftMaxH : rightMaxH) * (j - i);
            if (tempMax > maxA) maxA = tempMax;
            if (leftMaxH == rightMaxH) {
                while (i < j && height[i] <= leftMaxH) i++;
                while (i < j && height[j] <= rightMaxH) j--;
            }
            else if (leftMaxH < rightMaxH) {
                while (i < j && height[i] <= leftMaxH) i++;
            }
            else while (i < j && height[j] <= rightMaxH) j--;
        }
        return maxA;
    }


    /*
     罗马数字共有七个，即I(1)，V(5)，X(10)，L(50)，C(100)，D(500)，M(1000)。按照下面的规则可以表示任意正整数。
     重复数次：一个罗马数字重复几次，就表示这个数的几倍。
     右加左减：在一个较大的罗马数字的右边记上一个较小的罗马数字，表示大数字加小数字。
     在一个较大的数字的左边记上一个较小的罗马数字，表示大数字减小数字。
     但是，左减不能跨越等级。比如，99不可以用IC表示，用XCIX表示。
     加线乘千：在一个罗马数字的上方加上一条横线或者在右下方写M，表示将这个数字乘以1000，即是原数的1000倍。同理，如果上方有两条横线，即是原数的1000000倍。
     单位限制：同样单位只能出现3次，如40不能表示为XXXX，而要表示为XL。
     */


    /**
     思路1： 直接把 1, 2, ..., 9; 10, 20, 30, ..., 90; 100, 200, ..., 900; 1000, 2000, 3000 这些数字通过表存储起来，然后直接查表即可；
     */
    string romans[30] = {
            "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX",
            "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC",
            "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM",
            "M", "MM", "MMM"
    };

    // 104ms
    string intToRomanV1(int num) {
        vector<string> rs;
        int power = 0;
        while (num) {
            if (num % 10 > 0) {
                rs.push_back(romans[power * 9 + num % 10 - 1]);
            }
            power++;
            num /= 10;
        }
        stringstream ss;
        copy(rs.rbegin(), rs.rend(), std::ostream_iterator<string>(ss, ""));
        return ss.str();
    }


    /**
     思路2： 同样是查表，但是表中的特殊数字更少了，而且是正向拼接字符串，节省了很多时间和空间
     */
    string romanArr[13] {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    int numArr[13] {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    // 75ms
    string intToRoman(int num) {
        string res;
        int index = 0;
        while (num) {
            if (num >= numArr[index]) {
                res += romanArr[index];
                num -= numArr[index];
            }
            else {
                index++;
            }
        }
        return res;
    }



    int romanToInt(string s) {
        int res = 0;
        for (int  i = 0, len = int(s.length()); i < len; ++i) {
            char cur = s[i];
            if (cur == 'M') res += 1000;
            else if (cur == 'C') {
                auto next = char(i + 1 < len ? s[i + 1] : '\0');
                if (next == 'M') res += 900, ++i;
                else if (next == 'D') res += 400, ++i;
                else res += 100;
            }
            else if (cur == 'D') res += 500;
            else if (cur == 'X') {
                auto next = char(i + 1 < len ? s[i + 1] : '\0');
                if (next == 'C') res += 90, ++i;
                else if (next == 'L') res += 40, ++i;
                else res += 10;
            }
            else if (cur == 'L') res += 50;
            else if (cur == 'I') {
                auto next = char(i + 1 < len ? s[i + 1] : '\0');
                if (next == 'X') res += 9, ++i;
                else if (next == 'V') res += 4, ++i;
                else res += 1;
            }
            else if (cur == 'V') res += 5;
        }
        return res;
    }



    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 1) return strs[0];

        string str;
        if (!strs.empty()) {
            string firstStr = strs[0];
            char c;
            int size = static_cast<int>(strs.size());
            for (int i = 0, len = static_cast<int>(firstStr.length()); i < len; ++i) {
                c = firstStr[i];
                for (int j = 1; j < size; ++j) {
                    if (strs[j][i] != c) return str;
                }
                str.push_back(c);
            }
        }
        return str;
    }



    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int maxIndex = int(nums.size() - 1);
        for (int i = 0; i + 1 < maxIndex; ++i) {
            if (i == 0 || nums[i] != nums[i - 1]) {
                int left = i + 1;
                int right = maxIndex;
                int target = -nums[i];
                while (left < right) {
                    int sum = nums[left] + nums[right];
                    if (sum == target) {
                        res.emplace_back(vector<int>{-target, nums[left], nums[right]});
                        while (left < right && nums[left] == nums[++left]);
                        while (left < right && nums[right] == nums[--right]);
                    }
                    else if (sum < target) {
                        ++left;
                    }
                    else {
                        --right;
                    }
                }
            }
        }
        return res;
    }



    int threeSumClosest(vector<int>& nums, int target) {
        auto sumClosest = nums[0] + nums[1] + nums[2];
        sort(nums.begin(), nums.end());
        auto maxIndex = int(nums.size() - 1);
        for (int i = 0; i + 1 < maxIndex; ++i) {
            if (i == 0 || nums[i] != nums[i - 1]) {
                int left = i + 1;
                int right = maxIndex;
                bool nextBreak = false;
                while (left < right) {
                    int sum = nums[i] + nums[left] + nums[right];
                    if (sum == target) return sum;

                    if (abs(target - sumClosest) > abs(target - sum)) {
                        sumClosest = sum;
                    }
                    if (nextBreak) break;

                    if (sum < target) {
                        if (left + 1 < right) left++;
                        else if (right < maxIndex) {
                            right++;
                            nextBreak = true;
                        }
                        else break;
                    }
                    else {
                        if (left + 1 < right) right--;
                        else if (left > i + 1) {
                            left--;
                            nextBreak = true;
                        }
                        else break;
                    }
                }
            }
        }
        return sumClosest;
    }



    vector<string> letterCombinations(string digits) {
        vector<string> result;
        vector<string> mappings = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        for (char c : digits) {
            string mp = mappings[int(c - '0')];
            size_t curSize = result.size();
            if (curSize == 0) {
                for (char cc : mp) {
                    string str{cc};
                    result.push_back(str);
                }
            }
            else {
                for (size_t i = 1, size = mp.size(); i < size; ++i) {
                    char cc = mp[i];
                    for (size_t j = 0; j < curSize; ++j) {
                        result.emplace_back(result[j] + cc);
                    }
                }
                char cc = mp[0];
                for (size_t j = 0; j < curSize; ++j) {
                    result[j] += cc;
                }
            }
        }
        return result;
    }




    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if (nums.size() <= 3) return res;
        sort(nums.begin(), nums.end());
        if (nums.back() * 4 < target) return res;
        size_t maxIndex = nums.size() - 1;
        for (size_t i = 0; i + 2 < maxIndex; ++i) {
            if ((i == 0 || nums[i] != nums[i - 1]) && nums[i] * 4 <= target) {
                int target3Sum = target - nums[i];
                if (nums.back() * 3 < target3Sum) continue;
                for (size_t j = i + 1; j + 1 < maxIndex; ++j) {
                    if ((j == i + 1 || nums[j] != nums[j - 1]) && nums[j] * 3 <= target3Sum) {
                        int target2Sum = target3Sum - nums[j];
                        size_t left = j + 1;
                        size_t right = maxIndex;
                        while (left < right) {
                            int sum = nums[left] + nums[right];
                            if (sum == target2Sum) {
                                res.push_back({nums[i], nums[j], nums[left], nums[right]});
                                while (left < right && nums[left] == nums[++left]);
                                while (left < right && nums[right] == nums[--right]);
                            }
                            else if (sum < target2Sum) {
                                left++;
                            }
                            else {
                                right--;
                            }
                        }
                    }
                }
            }
        }
        return res;
    }



    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        while (n-- > 0) {
            if (!fast) return head;
            fast = fast->next;
        }
        if (fast) {
            ListNode *slow = head;
            while (fast) {
                fast = fast->next;
                if (!fast) {
                    slow->next = slow->next->next;
                    return head;
                }
                else slow = slow->next;
            }
        }
        else return head->next;
    }


    //https://leetcode.com/problems/valid-parentheses/description/
    bool isValid(string s) {
        size_t len = s.size();
        if (len == 0) return true;
        if (len % 2 == 1) return false;

        stack<char> lefts;
        for (size_t i = 0; i < len; ++i) {
            char c = s[i];
            if (c == '(' || c == '[' || c == '{') {
                lefts.push(c);
            }
            else {
                if (lefts.empty()) return false;
                char last = lefts.top();
                lefts.pop();
                if (((last == '(' && c == ')'))
                    || ((last == '[' && c == ']'))
                    || ((last == '{' && c == '}'))) {

                }
                else return false;
            }
        }
        return lefts.empty();
    }



    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        else if (l2 == nullptr) return l1;

        ListNode tempHead = ListNode(0);
        ListNode *cur = &tempHead;
        while (true) {
            if (l1 != nullptr && l2 != nullptr) {
                if (l1->val <= l2->val) {
                    cur->next = l1;
                    l1 = l1->next;
                }
                else {
                    cur->next = l2;
                    l2 = l2->next;
                }
                cur = cur->next;
            }
            else if (l1 != nullptr) {
                cur->next = l1;
                break;
            }
            else {
                cur->next = l2;
                break;
            }
        }
        return tempHead.next;
    }



    vector<string> generateParenthesis(int n) {
        vector<string> res;
        if (n > 0) {
            vector<int> leftNums;
            string fisrt{'('};
            res.push_back(fisrt);
            leftNums.push_back(1);
            for (int i = 1, size = n * 2; i < size; ++i) {
                auto curSize = int(res.size());
                for (int j = 0; j < curSize; ++j) {
                    auto leftNum = leftNums[j] + (int(res[j].size()) - leftNums[j]) / 2;
                    if (leftNum < n && leftNums[j] > 0) {
                        res.push_back(res[j] + ')');
                        res[j].push_back('(');
                        leftNums.push_back(leftNums[j] - 1);
                        leftNums[j]++;
                    }
                    else if (leftNum < n) {
                        res[j].push_back('(');
                        leftNums[j]++;
                    }
                    else {
                        res[j].push_back(')');
                        leftNums[j]--;
                    }
                }
            }
        }
        return res;
    }



    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        int left, right;
        while ((right = lists.size() - 1) != 0) {
            left = 0;
            while (left < right) {
                lists[left] = mergeTwoLists(lists[left], lists[right]);
                lists.pop_back();
                left++;
                right--;
            }
        }
        return lists[0];
    }



    ListNode* swapPairs(ListNode* head) {
        if (head && !head->next) return head;
        ListNode tempHead(0);
        ListNode *cur = &tempHead;
        ListNode *next = head;
        while (next) {
            if (next->next) {
                cur->next = next->next;
                next->next = next->next->next;
                cur->next->next = next;
                cur = next;
                next = next->next;
            }
            else break;
        }
        return tempHead.next;
    }



    ListNode* reverseKGroupV1(ListNode* head, int k) {
        if (k <= 1) return head;

        ListNode *tail = nullptr;
        ListNode *tempTail = nullptr;
        ListNode *newHead = nullptr;
        ListNode *tempHead;
        ListNode *reverseNext = nullptr;
        ListNode *tempReverseNext = nullptr;
        ListNode *next = head;
        while (next) {
            reverseNext = next;
            tempTail = next;
            tempHead = nullptr;

            int index = 0;
            while (next && index < k) {
                next = next->next;
                index++;
            }

            if (index == k) {
                while (reverseNext != next) {
                    tempReverseNext = reverseNext->next;
                    reverseNext->next = tempHead;
                    tempHead = reverseNext;
                    reverseNext = tempReverseNext;
                }
                if (!newHead) newHead = tempHead;
                if (tail) tail->next = tempHead;
                tail = tempTail;
            }
            else {
                if (tail) tail->next = tempTail;
                break;
            }
        }
        return newHead == nullptr ? head : newHead;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k <= 1 || !head || !head->next) return head;
        int len = 0;
        ListNode *cur = head;
        while (cur) {
            len++;
            cur = cur->next;
        }

        if (len < k) return head;
        ListNode tempHead(0);
        ListNode *newHead = &tempHead;
        ListNode *groupHead = nullptr;
        ListNode *tail = newHead;
        ListNode *tempTail;
        cur = head;
        for (int i = 0, n = len / k; i < n; ++i) {
            tempTail = cur;
            for (int j = 0; j < k; ++j) {
                tail->next = cur->next;
                cur->next = groupHead;
                groupHead = cur;
                cur = tail->next;
            }
            tail->next = groupHead;
            tail = tempTail;
        }
        tail->next = cur;
        return newHead->next;
    }



    int removeDuplicates(vector<int>& nums) {
        auto size = int(nums.size());
        if (size <= 1) return size;
        int count = 1;
        for (int i = 1; i < size; ++i) {
            if (nums[count - 1] != nums[i]) {
                nums[count++] = nums[i];
            }
        }
        return count;
    }



    int removeElement(vector<int>& nums, int val) {
        if (nums.empty()) return 0;

        int count = 0;
        for (int i = 0, size = int(nums.size()); i < size; ++i) {
            if (nums[i] != val) {
                nums[count++] = nums[i];
            }
        }
        return count;
    }



    int strStr(const string &haystack, const string &needle) {
        auto len1 = int(haystack.size());
        auto len2 = int(needle.size());
        if (len2 == 0) return 0;
        if (len2 > len1) return -1;
        for (int i = 0, j; i <= len1 - len2; ++i) {
            j = 0;
            for (; j < len2; ++j) {
                if (haystack[i + j] != needle[j]) break;
            }
            if (j == len2) return i;
        }
        return -1;
    }



    void lastMatchIndex(const string &str, vector<int> &lastMatch) {
        lastMatch.push_back(-1);
        int matchIndex = -1;
        for (int compareIndex = 1, len = int(str.size()); compareIndex < len; ++compareIndex) {
            while (matchIndex > -1 && str[matchIndex + 1] != str[compareIndex]) {
                matchIndex = lastMatch[matchIndex];
            }
            if (str[matchIndex + 1] == str[compareIndex]) {
                matchIndex++;
            }
            lastMatch.push_back(matchIndex);
        }
    }

    int strStrKmp(const string &haystack, const string &needle) {
        auto len1 = int(haystack.size());
        auto len2 = int(needle.size());
        if (len2 == 0) return 0;
        if (len2 > len1) return -1;

        int matchIndex = -1;
        vector<int> lastMatchs;
        lastMatchIndex(needle, lastMatchs);
        for (int i = 0; i < len1; ++i) {
            while (matchIndex > -1 && needle[matchIndex + 1] != haystack[i]) {
                matchIndex = lastMatchs[matchIndex];
            }
            if (needle[matchIndex + 1] == haystack[i]) {
                matchIndex++;
            }
            if (matchIndex == len2 - 1) return i - len2 + 1;
        }
        return -1;
    }



    int divide(int dividend, int divisor) {
        if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
        if (divisor == 1) return dividend;
        if (dividend == -1) return -dividend;

        bool sameMark = (dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0);
        if (dividend > 0) dividend = -dividend;
        if (divisor > 0) divisor = -divisor;
        if (dividend > divisor) return 0;

        vector<int> mutils {divisor};
        vector<int> times {1};
        int lastMutil;
        int lastTime;
        while (true) {
            lastMutil = mutils.back();
            if (dividend - lastMutil > lastMutil) break;
            mutils.push_back(lastMutil + lastMutil);
            lastTime = times.back();
            times.push_back(lastTime + lastTime);
        }
        int res = times.back();
        int sum = mutils.back();
        for (auto i = int(mutils.size() - 2); i >= 0; ) {
            if (dividend - sum == mutils[i]) {
                res += times[i];
                break;
            }
            else if (dividend - sum < mutils[i]) {
                sum += mutils[i];
                res += times[i];
            }
            else {
                --i;
            }
        }
        return sameMark ? res : -res;
    }



    class CharTree {

        enum CharNodeType {
            root,
            trunk,
            leaf
        };

        class CharNode {
        public:
            CharNodeType type;
            int reachCount = 0;
            int expectedReachCount = 0;
            char value;
            unordered_map<char, shared_ptr<CharNode>> children{};

            CharNode(CharNodeType type, char value) : type(type), value(value) {}

            shared_ptr<CharNode> addChild(CharNodeType type, char value) {
                auto it = children.find(value);
                if (it == children.end()) {
                    auto temp = shared_ptr<CharNode>(new CharNode(type, value));
                    temp->expectedReachCount = 1;
                    children[value] = temp;
                    return temp;
                }
                else {
                    it->second->expectedReachCount++;
                    return it->second;
                }
            }
        };

        int wordLen;

        int wordNum = 0;

        CharNode rootNode = CharNode(root, '\0');

        vector<shared_ptr<CharNode>> leaves{};

    public:

        explicit CharTree(int wordLen) : wordLen(wordLen) {}

        void resetReachCount() {
            for (auto &leaf : leaves) {
                leaf->reachCount = 0;
            }
        }

        void addWord(const string &str) {
            wordNum++;
            CharNode *cur = &rootNode;
            for (int i = 0, len = int(str.size()); i < len; ++i) {
                auto child = cur->addChild(i + 1 == len ? leaf : trunk, str[i]);
                if (child->type == leaf) leaves.push_back(child);
                cur = child.get();
            }
        }

        void addWords(const vector<string> &strs) {
            for (auto &str : strs) {
                addWord(str);
            }
        }

        bool match(const string &str, int from) {
            CharNode *cur;
            for (int i = 0, checkLen = wordNum * wordLen; i < checkLen; ++i) {
                if (i % wordLen == 0) cur = &rootNode;
                auto it = cur->children.find(str[from + i]);
                if (it == cur->children.cend()) {
                    return false;
                }
                if (it->second->type == leaf) {
                    if (it->second->reachCount >= it->second->expectedReachCount) return false;
                    else it->second->reachCount++;
                }
                cur = it->second.get();
            }
            for (auto &leaf : leaves) {
                if (leaf->reachCount != leaf->expectedReachCount) return false;
            }
            return true;
        }

    };

    // 134ms
    vector<int> findSubstringV1(const string &s, vector<string>& words) {
        vector<int> res;
        if (!words.empty()) {
            auto len = int(words[0].length());
            CharTree charTree(len);
            charTree.addWords(words);
            for (int i = 0, maxIndex = int(s.length() - len * words.size()); i <= maxIndex; ++i) {
                if (charTree.match(s, i)) res.push_back(i);
                charTree.resetReachCount();
            }
        }
        return res;
    }

    // 111ms
    vector<int> findSubstringV2(const string &s, vector<string>& words) {
        vector<int> res;
        if (!words.empty()) {
            auto wordLen = int(words[0].length());
            auto wordNum = int(words.size());
            unordered_map<string, int> wordCount;
            unordered_map<string, int> tempCount;
            for (auto &word : words) {
                wordCount[word]++;
            }
            for (int i = 0, maxIndex = int(s.length() - wordLen * wordNum); i <= maxIndex; ++i) {
                int matchNum = 0;
                for (int j = 0; j < wordNum; ++j) {
                    auto subStr = s.substr(i + j * wordLen, wordLen);
                    auto it = wordCount.find(subStr);
                    if (it == wordCount.end()) {
                        break;
                    }
                    else {
                        int temp = ++(tempCount[subStr]);
                        if (temp > it->second) {
                            break;
                        }
                        else if (temp == it->second) {
                            matchNum++;
                        }
                    }
                }
                tempCount.clear();
                if (matchNum == wordCount.size()) res.push_back(i);
            }
        }
        return res;
    }

    // 26ms
    vector<int> findSubstringV3(const string &s, vector<string>& words) {
        vector<int> res;
        int sLen, wordLen, wordNum, checkWidth;
        if ((sLen = int(s.length())) == 0
            || (wordNum = int(words.size())) == 0
            || (wordLen = int(words[0].length())) == 0
            || (checkWidth = wordNum * wordLen) == 0) {
            return res;
        }

        if (wordNum == 1) {
            for (int i = 0, maxI = sLen - wordLen; i <= maxI; ++i) {
                if (s.substr(i, wordLen) == words[0]) {
                    res.push_back(i);
                }
            }
            return res;
        }

        vector<int> count;
        unordered_map<string, int> wordIndexes;
        for (auto &item : words) {
            auto it = wordIndexes.find(item);
            if (it != wordIndexes.end()) {
                count[it->second]++;
            }
            else {
                count.push_back(1);
                wordIndexes.insert(it, {item, int(wordIndexes.size())});
            }
        }

        vector<int> sIndexes;
        for (int i = 0, maxI = sLen - wordLen; i <= maxI; ++i) {
            auto it = wordIndexes.find(s.substr(i, wordLen));
            sIndexes.push_back(it != wordIndexes.end() ? it->second : -1);
        }

        vector<int> tempCount = count;
        for (int i = 0, maxIndex = sLen - checkWidth; i <= maxIndex; ++i) {
            int matchNum = 0;
            for (int j = 0; j < wordNum; ++j) {
                int matchIndex = sIndexes[i + j * wordLen];
                if (matchIndex == -1) break;
                auto tempC = --tempCount[matchIndex];
                if (tempC == 0) matchNum++;
                else if (tempC < 0) {
                    matchNum--;
                    break;
                }
            }
            if (matchNum == count.size()) res.push_back(i);
            tempCount = count;
        }

        return res;
    }

    // 24ms
    vector<int> findSubstring(const string &s, vector<string>& words) {
        vector<int> res;
        int sLen, wordLen, wordNum, checkWidth;
        if ((sLen = int(s.length())) == 0
            || (wordNum = int(words.size())) == 0
            || (wordLen = int(words[0].length())) == 0
            || (checkWidth = wordNum * wordLen) == 0) {
            return res;
        }

        if (wordNum == 1) {
            for (int i = 0, maxI = sLen - wordLen; i <= maxI; ++i) {
                if (s.substr(i, wordLen) == words[0]) {
                    res.push_back(i);
                }
            }
            return res;
        }

        default_random_engine generator;
        uniform_int_distribution<int> distribution(1, 10000);
        int wordHashSum = 0;
        unordered_map<string, int> wordHash;
        for (auto &item : words) {
            auto it = wordHash.find(item);
            if (it != wordHash.end()) {
                wordHashSum += it->second;
            }
            else {
                auto h = distribution(generator);
                wordHash.insert(it, {item, h});
                wordHashSum += h;
            }
        }

        vector<int> sIndexes;
        for (int i = 0, maxI = sLen - wordLen; i <= maxI; ++i) {
            auto it = wordHash.find(s.substr(i, wordLen));
            sIndexes.push_back(it != wordHash.end() ? it->second : -1);
        }

        for (int i = 0, maxIndex = sLen - checkWidth; i <= maxIndex; ++i) {
            int hashSum = 0;
            for (int j = 0; j < wordNum; ++j) {
                int h = sIndexes[i + j * wordLen];
                if (h == -1) break;
                hashSum += h;
            }
            if (hashSum == wordHashSum) res.push_back(i);
        }

        return res;
    }

    void test() {




//        {
//            string str {"barfoothefoobarman"};
//            vector<string> words {"foo", "bar"};
//            cout << findSubstring(str, words) << endl;
//        }
//        {
//            string str {"wordgoodgoodgoodbestword"};
//            vector<string> words {"word","good","best","good"};
//            cout << findSubstring(str, words) << endl;
//        }



//        {
//            cout << divide(1, 2) << endl;
//            cout << divide(125, 25) << endl;
//            cout << divide(125, -25) << endl;
//            cout << divide(-2147483648, 2) << endl;
//            cout << divide(INT_MAX, 25) << endl;
//            cout << divide(INT_MAX, -25) << endl;
//            cout << divide(INT_MIN, 25) << endl;
//            cout << divide(INT_MIN, -25) << endl;
//        }



//        {
//            cout << strStrKmp("hello", "ll") << endl;
//            cout << strStr("hello", "hello") << endl;
//            cout << strStr("hello", "") << endl;
//            cout << strStr("", "hello") << endl;
//        }



//        {
//            vector<int> nums{1,1,2,2,3,3,3};
//            cout << removeElement(nums, 3) << endl;
//            cout << nums << endl;
//        }



//        {
//            vector<int> nums{1,1,2,2,3,3,3};
//            cout << removeDuplicates(nums) << endl;
//            cout << nums << endl;
//        }


//        {
//            auto l1 = ListNode::parse("1->2->3->4->5->6");
//            cout << *reverseKGroup(l1, 3) << endl;
//        }



//        {
//            auto l1 = ListNode::parse("1->2->3");
//            cout << *swapPairs(l1) << endl;
//        }



//        {
//            auto l1 = ListNode::parse("1->3->5");
//            auto l2 = ListNode::parse("2->3->6");
//            auto l3 = ListNode::parse("0->2->4");
//            vector<ListNode*> lists{l1, l2, l3};
//            cout << *mergeKLists(lists) << endl;
//        }



//        {
//            cout << generateParenthesis(2) << endl;
//        }


//        {
//            ListNode *l1 = ListNode::parse("1->2->4");
//            ListNode *l2 = ListNode::parse("1->3->4->5");
//            cout << *mergeTwoLists(l1, l2) << endl;
//        }



//        {
//            cout << isValid("([{}])") << endl;
//        }



//        {
//            auto head = ListNode::parse("1->2->3->4->5");
//            int removeIndex = 2;
//            cout << *removeNthFromEnd(head, removeIndex) << endl;
//        }
//        {
//            auto head = ListNode::parse("1->2");
//            int removeIndex = 2;
//            cout << *removeNthFromEnd(head, removeIndex) << endl;
//        }


//        {
//            vector<int> nums{1, 0, -1, 0, -2, 2};
//            int target = 0;
//            auto res = fourSum(nums, target);
//            for_each(res.begin(), res.end(), [](vector<int> &item) {
//               cout << item << endl;
//            });
//            cout << endl;
//        }
//        {
//            vector<int> nums{2,1,0,-1};
//            int target = 2;
//            auto res = fourSum(nums, target);
//            for_each(res.begin(), res.end(), [](vector<int> &item) {
//                cout << item << endl;
//            });
//            cout << endl;
//        }



//        {
//            auto res = letterCombinations("234");
//            cout << res << endl;
//        }



//        {
//            vector<int> nums{-3,-2,-5,3,-4};
//            int target = -1;
//            cout << threeSumClosest(nums, target) << endl;
//        }
//        {
//            vector<int> nums{-55,-24,-18,-11,-7,-3,4,5,6,9,11,23,33};
//            int target = 0;
//            cout << threeSumClosest(nums, target) << endl;
//        }




////        vector<int> nums{-2,0,0,2,2};
//        vector<int> nums{-1, 0, 1, 2, -1, -4};
//        auto res = threeSum(nums);
//        for (auto &item : res) {
//            cout << item << endl;
//        }


//        vector<string> strs {
//                "abcd",
//                "abc",
//                "ab"
//        };
//        cout << longestCommonPrefix(strs) << endl;


//        cout << romanToInt(intToRoman(3786)) << endl;
//        cout << intToRoman(3786) << endl;


//        vector<int> heights {1,2,3,2,4,1,2,3,4,1};
//        cout << maxArea(heights) << endl;


//        cout << isMatch("aa", "aa*a") << endl;
//        cout << isMatch("babcacacbbbacbaabbb", ".*.*b*ab*a*aa*b*.*c") << endl;
//        cout << isMatch("aa", "a") << endl;
//        cout << isMatch("aa", "a.") << endl;
//        cout << isMatch("aa", "a*") << endl;
//        cout << isMatch("ab", ".*") << endl;
//        cout << isMatch("", "a*") << endl;
//        cout << isMatch("", "") << endl;
//        cout << isMatch("", ".") << endl;
//        cout << isMatch("abcddde", "a.cd*e") << endl;


//        cout << isPalindrome(2147447412) << endl;


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


//        auto listNode1 = ListNode::parse("2 -> 4 -> 3");
//        auto listNode2 = ListNode::parse("5 -> 6 -> 4");
//        cout << *addTwoNumbers(listNode1, listNode2) << endl;


//        int target = -8;
//        vector<int> nums {-1,-2,-3,-4,-5};
//        cout << twoSum(nums, target) << endl;


    }

};


#endif //C_ACM_SOLUTIONS_H
