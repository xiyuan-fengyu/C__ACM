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



    bool isMatch_regexMatching(const string &s, const string &p) {
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




    void nextPermutation(vector<int>& nums) {
        auto size = int(nums.size());
        if (size > 1) {
            int i = size - 2;
            for (; i > -1; --i) {
                if (nums[i] < nums[i + 1]) {
                    for (int j = size - 1; j > i; --j) {
                        if (nums[i] < nums[j]) {
                            int temp = nums[i];
                            nums[i] = nums[j];
                            nums[j] = temp;
                            goto afterLoops;
                        }
                    }
                }
            }

            afterLoops:
            sort(nums.begin() + i + 1, nums.end());
        }
    }



    //12ms
    int longestValidParenthesesV1(const string &str) {
        auto len = int(str.length());
        if (len <= 1) return 0;

        int maxLen = 0;
        vector<array<int, 2>> pairs;
        for (int i = 0; i < len; ++i) {
            char c = str[i];
            if (c == '(') {
                pairs.emplace_back(array<int, 2>{i, -2});
            }
            else {
                if (pairs.empty()) {
                    pairs.emplace_back(array<int, 2>{-2, i});
                }
                else {
                    bool requireMerge = false;
                    auto &last = pairs.back();
                    if (last[0] != -2 && last[1] == -2) {
                        last[1] = i;
                        requireMerge = true;
                    }
                    else if (pairs.size() > 1 && last[0] != -2 && last[1] != -2) {
                        auto &beforeLast = pairs[pairs.size() - 2];
                        if (beforeLast[0] + 1 == last[0] && beforeLast[1] == -2) {
                            beforeLast[1] = i;
                            pairs.pop_back();
                            requireMerge = true;
                        }
                    }

                    if (requireMerge) {
                        int size;
                        while ((size = int(pairs.size())) > 1) {
                            auto &last1 = pairs.back();
                            auto &beforeLast = pairs[size - 2];
                            if (beforeLast[0] != -2 && beforeLast[1] + 1 == last1[0] && last1[1] != -2) {
                                beforeLast[1] = last1[1];
                                pairs.pop_back();
                            }
                            else break;
                        }
                    }

                    auto &last2 = pairs.back();
                    if (last2[0] != -2 && last2[1] != -2) {
                        maxLen = max(maxLen, last2[1] - last2[0] + 1);
                    }
                }
            }
        }
        return maxLen;
    }

    //12ms
    int longestValidParenthesesV2(const string &str) {
        auto len = int(str.length());
        if (len <= 1) return 0;

        int maxLen = 0;
        for (int i = 0, count = 0, left = -1; i < len; ++i) {
            if (str[i] == '(') {
                if (count++ == 0 && left == -1) {
                    left = i;
                }
            }
            else {
                if (--count == 0) {
                    maxLen = max(maxLen, i - left + 1);
                }
                else if (count < 0) {
                    count = 0;
                    left = -1;
                }
            }
        }

        for (int i = len - 1, count = 0, right = len; i > -1; --i) {
            if (str[i] == ')') {
                if (count++ == 0 && right == len) {
                    right = i;
                }
            }
            else {
                if (--count == 0) {
                    maxLen = max(maxLen, right - i + 1);
                }
                else if (count < 0) {
                    count = 0;
                    right = len;
                }
            }
        }
        return maxLen;
    }

    //10ms
    int longestValidParentheses(const string &str) {
        auto len = int(str.length());
        if (len <= 1) return 0;

        int maxLen = 0;
        int count = 0;
        stack<int> unMatchs{};
        for (int i = 0, left = -1; i < len; ++i) {
            if (str[i] == '(') {
                unMatchs.push(i);
                if (count++ == 0 && left == -1) {
                    left = i;
                }
            }
            else {
                if (!unMatchs.empty()) unMatchs.pop();

                --count;
                if (count == 0) {
                    maxLen = max(maxLen, i - left + 1);
                }
                else if (count > 0) {
                    maxLen = max(maxLen, i - unMatchs.top());
                }
                else if (count < 0) {
                    count = 0;
                    left = -1;
                }
            }
        }
        return maxLen;
    }




    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        int left = 0;
        int right = int(nums.size() - 1);
        int mid, midV, leftV, rightV;
        while (left < right) {
            leftV = nums[left];
            rightV = nums[right];
            midV = nums[mid = (left + right) / 2];
            if (midV <= rightV) {
                if (midV < target && target <= rightV) left = mid + 1;
                else right = mid;
            }
            else {
                if (midV >= target && target >= leftV) right = mid;
                else left = mid + 1;
            }
        }

        if (nums[left] == target) return left;
        return -1;
    }



    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty() || target < nums[0] || target > nums.back()) {
            return vector<int> {-1 , -1};
        }

        return searchRange(nums, target, 0, nums.size() - 1);
    }

    vector<int> searchRange(vector<int>& nums, int target, int left, int right) {
        if (left > right) return vector<int> {-1 , -1};
        int mid = (left + right) / 2;
        int midV = nums[mid];
        if (target < midV) {
            return searchRange(nums, target, left, mid - 1);
        }
        else if (target > midV) {
            return searchRange(nums, target, mid + 1, right);
        }
        else {
            return vector<int> {
                searchLeftEdge(nums, target, left, mid),
                searchRightEdge(nums, target, mid, right)
            };
        }
    }

    int searchLeftEdge(vector<int>& nums, int target, int left, int right) {
        if (left > right) return -1;

        int mid = (left + right) / 2;
        int midV = nums[mid];
        if (target > midV) {
            return searchLeftEdge(nums, target, mid + 1, right);
        }
        else if (target == midV) {
            int leftSub = searchLeftEdge(nums, target, left, mid - 1);
            return leftSub == -1 ? mid : leftSub;
        }
        else return -1;
    }

    int searchRightEdge(vector<int>& nums, int target, int left, int right) {
        if (left > right) return -1;

        int mid = (left + right) / 2;
        int midV = nums[mid];
        if (target < midV) {
            return searchRightEdge(nums, target, left, mid - 1);
        }
        else if (target == midV) {
            int rightSub = searchRightEdge(nums, target, mid + 1, right);
            return rightSub == -1 ? mid : rightSub;
        }
        else return -1;
    }


    int searchInsert(vector<int>& nums, int target) {
        if (nums.empty() || target <= nums.front()) return 0;

        auto back = nums.back();
        auto size = int(nums.size());
        if (target == back) return size - 1;
        else if (target > back) return size;

        int left = 1;
        int right = size - 2;
        while (left <= right) {
            int mid = (left + right) / 2;
            int midV = nums[mid];
            if (midV == target) return mid;
            else if (midV < target) left = mid + 1;
            else right = mid - 1;
        }
        return right + 1;
    }



    void buildSudokuVector(vector<vector<char>> &board, const string &chars) {
        board.clear();
        int index = 0;
        vector<char> line;
        for (char c : chars) {
            if (c == '.' || (c >= '1' && c <= '9')) {
                if (index != 0 && index % 9 == 0) {
                    board.push_back(line);
                    line = vector<char>();
                }
                line.push_back(c);
                index++;
            }
        }
        board.push_back(line);
    }

    bool isValidSudoku(vector<vector<char>>& board) {
        int check = 0;
        for (int i = 0; i < 9; ++i) {
            // 检查行
            check = 0;
            for (int j = 0; j < 9; ++j) {
                auto c = board[i][j];
                if (c != '.') {
                    int bit = 1 << int(c - '1');
                    if (check & bit) return false;
                    check |= bit;
                }
            }

            // 检查列
            check = 0;
            for (int j = 0; j < 9; ++j) {
                auto c = board[j][i];
                if (c != '.') {
                    int bit = 1 << int(c - '1');
                    if (check & bit) return false;
                    check |= bit;
                }
            }

            // 检查9格
            check = 0;
            for (int j = 0; j < 9; ++j) {
                auto index = i / 3 * 27 + i % 3 * 3 + j / 3 * 9 + j % 3;
                auto c = board[index / 9][index % 9];
                if (c != '.') {
                    int bit = 1 << int(c - '1');
                    if (check & bit) return false;
                    check |= bit;
                }
            }
        }
        return true;
    }


    void solveSudoku(vector<vector<char>>& board) {
        array<array<int, 3>, 81> validNums {};
        for (int i = 0; i < 81; ++i) {
            int row = i / 9;
            int col = i % 9;
            char c = board[row][col];
            if (c == '.') {
                validNums[i][0] = 511;
                validNums[i][1] = 9;
                validNums[i][2] = 0;
            }
            else {
                validNums[i][0] = 0;
                validNums[i][1] = 0;
                validNums[i][2] = c - '0';
            }
        }

        for (int i = 0; i < 81; ++i) {
            if (validNums[i][2] != 0) {
                reduceValidNum(i / 9, i % 9, validNums, nullptr);
            }
        }

        int minRemainPos = getRemainMinPos(validNums);
        tryValidNum(minRemainPos, validNums);

        for (int i = 0; i < 81; ++i) {
            int row = i / 9;
            int col = i % 9;
            board[row][col] = char(validNums[i][2] + '0');
        }
    }

    bool tryValidNum(int pos, array<array<int, 3>, 81> &validNums) {
        auto& validNum = validNums[pos];
        int validNumBit = validNum[0];
        int num = 1;
        while (validNumBit > 0) {
            if ((validNumBit & 1) > 0) {
                vector<array<int, 2>> changes {};
                validNum[2] = num;
                reduceValidNum(pos / 9, pos % 9, validNums, &changes);

                int minRemainPos = getRemainMinPos(validNums);
                if (minRemainPos == 81) return true;
                else if (minRemainPos > -1) {
                    bool subRes = tryValidNum(minRemainPos, validNums);
                    if (subRes) return true;
                }

                rollbackValidNums(validNums, &changes);
            }
            num++;
            validNumBit >>= 1;
        }
        validNum[2] = 0;
        return false;
    }

    void reduceValidNum(int row, int col, array<array<int, 3>, 81> &validNums, vector<array<int, 2>> *changes) {
        int curPos = row * 9 + col;
        int num = validNums[curPos][2];
        int numBit = 1 << (num - 1);

        // 减少当前行的剩余可用数字信息
        for (int i = 0; i < 9; ++i) {
            if (i != col) {
                int pos = row * 9 + i;
                reduceValidNum(numBit, pos, validNums[pos], changes);
            }
        }

        // 减少当前列的剩余可用数字信息
        for (int i = 0; i < 9; ++i) {
            if (i != row) {
                int pos = i * 9 + col;
                reduceValidNum(numBit, pos, validNums[pos], changes);
            }
        }

        // 减少九宫格的剩余可用数字信息
        int ltIndex = curPos / 27 * 27 + curPos % 9 / 3 * 3;
        for (int j = 0; j < 9; ++j) {
            auto pos = ltIndex + j / 3 * 9 + j % 3;
            reduceValidNum(numBit, pos, validNums[pos], changes);
        }
    }

    void reduceValidNum(int numBit, int pos, array<int, 3> &validNum, vector<array<int, 2>> *changes) {
        if (validNum[2] == 0) {
            if ((validNum[0] & numBit) != 0) {
                validNum[0] -= numBit;
                validNum[1] -= 1;
                if (changes != nullptr) {
                    changes->push_back(array<int, 2>{pos, numBit});
                }
            }
        }
    }

    int getRemainMinPos(array<array<int, 3>, 81> &validNums) {
        int minRemain = -1;
        int minRemainPos = 81;
        for (int i = 0; i < 81; ++i) {
            auto validNum = validNums[i];
            if (validNum[1] == 0) {
                if (validNum[2] == 0) return -1;
            }
            else if (validNum[2] == 0) {
                if (minRemain == -1 || minRemain > validNum[1]) {
                    minRemain = validNum[1];
                    minRemainPos = i;
                }
            }
        }
        return minRemainPos;
    }

    void rollbackValidNums(array<array<int, 3>, 81> &validNums, vector<array<int, 2>> *changes) {
        for (auto change : *changes) {
            auto& validNum = validNums[change[0]];
            validNum[0] |= change[1];
            validNum[1]++;
        }
    }



    string countAndSay(int n) {
        if (n == 1) {
            return "1";
        }

        string str = "1";
        for (int i = 2; i <= n; ++i) {
            stringstream buffer {};
            for (int j = 0, len = str.length(); j < len; ) {
                for (int k = j + 1; k <= len; ) {
                    if (k == len || str[k] != str[j]) {
                        buffer << k - j << str[j];
                        j = k;
                        break;
                    }
                    else {
                        k++;
                    }
                }
            }
            str = buffer.str();
        }
        return str;
    }

    // TODO 待优化
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res {};
        sort(candidates.begin(), candidates.end());
        combinationSum(res, candidates, 0, target);
        return res;
    }

    void combinationSum(vector<vector<int>> &res, vector<int>& candidates, int index, int target) {//, unordered_map<int, vector<tuple<int, vector<vector<int>>*>>>& targetCaches
        if (index >= candidates.size() || candidates[index] > target) {
            return;
        }

        int size = res.size();
        auto curValue = candidates[index];
        if (curValue == target) {
            res.push_back(vector<int> {target});
        }
        else {
            combinationSum(res, candidates, index, target - curValue);
            int newSize0 = res.size();
            if (newSize0 > size) {
                for (int i = size; i < newSize0; ++i) {
                    auto& resItem = res[i];
                    resItem.insert(resItem.begin(), curValue);
                }
            }

            combinationSum(res, candidates, index + 1, target);
        }
    }


    // TODO 待优化
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res {};
        sort(candidates.begin(), candidates.end());
        combinationSum2(res, candidates, 0, target);
        return res;
    }

    void combinationSum2(vector<vector<int>> &res, vector<int>& candidates, int index, int target) {
        int numSize = candidates.size();
        if (index >= numSize || candidates[index] > target) {
            return;
        }

        auto curValue = candidates[index];
        if (curValue == target) {
            res.push_back(vector<int> {target});
        }
        else {
            int resSize = res.size();
            combinationSum2(res, candidates, index + 1, target - curValue);
            int resSize0 = res.size();
            if (resSize0 > resSize) {
                for (int i = resSize; i < resSize0; ++i) {
                    auto& resItem = res[i];
                    resItem.insert(resItem.begin(), curValue);
                }
            }

            int nextIndex = index + 1;
            while (nextIndex < numSize) {
                if (candidates[nextIndex] != candidates[index]) {
                    combinationSum2(res, candidates, nextIndex, target);
                    break;
                }
                nextIndex++;
            }
        }
    }


    int firstMissingPositive(vector<int>& nums) {
        int size = nums.size();
        for (int i = 0; i < size; ++i) {
            int curIndex = i;
            int swapToValue = -1;
            int curValue;
            while (curIndex > -1 && nums[curIndex] != curIndex + 1) {
                curValue = nums[curIndex];
                nums[curIndex] = swapToValue;
                if (curValue <= size) {
                    swapToValue = curValue;
                    curIndex = curValue - 1;
                }
            }
        }

        for (int i = 0; i < size; ++i) {
            if (nums[i] <= 0) {
                return i + 1;
            }
        }
        return size + 1;
    }


    int trapV1(vector<int>& height) {
        int res = 0;
        vector<array<int, 2>> heightIndexes {};
        for (int i = 0, size = height.size(); i < size; ++i) {
            auto h = height[i];
            if (i == 0) {
                heightIndexes.push_back({h, i});
            }
            else {
                auto& lastHeightIndex = heightIndexes.back();
                auto lastHeight = lastHeightIndex[0];
                if (lastHeight == h) {
                    lastHeightIndex[1] = i;
                }
                else {
                    while (lastHeight <= h) {
                        if (lastHeight < h) {
                            auto curHISize = heightIndexes.size();
                            if (curHISize == 1) {
                                heightIndexes.pop_back();
                                break;
                            }
                            else {
                                auto& prevHeightIndex = heightIndexes[curHISize - 2];
                                auto prevHeight = prevHeightIndex[0];
                                res += (min(prevHeight, h) - lastHeight) * (i - prevHeightIndex[1] - 1);
                                heightIndexes.pop_back();
                                lastHeightIndex = prevHeightIndex;
                                lastHeight = prevHeight;
                            }
                        }
                        else {
                            heightIndexes.pop_back();
                            break;
                        }
                    }
                    heightIndexes.push_back({h, i});
                }
            }
        }
        return res;
    }

    int trap(vector<int>& height) {
        int res = 0;
        int size = height.size();
        if (size <= 2) {
            return res;
        }

        int rMax = 0;
        vector<int> rMaxs(size, 0);
        for (int i = size - 1; i >= 0; --i) {
            if (rMax < height[i]) {
                rMax = height[i];
            }
            rMaxs[i] = rMax;
        }

        int lMax = height[0];
        for (int i = 1; i < size - 1; ++i) {
            int h = height[i];
            rMax = rMaxs[i + 1];
            if (lMax > h) {
                if (rMax > h) {
                    res += min(lMax, rMax) - h;
                }
            }
            else if (lMax < h) {
                lMax = h;
            }
        }
        return res;
    }




    // @TODO 待优化
    string multiply(const string& numStr1, const string& numStr2) {
        if (numStr1 == "0" || numStr2 == "0") {
            return "0";
        }

        string res = "0";
        for (int i = 0, len2 = numStr2.length(); i < len2; ++i) {
            string tempMultiply = multiply(numStr1, numStr2[len2 - i - 1] - '0', i);
            res = plus(res, tempMultiply);
        }
        return res;
    }

    string multiply(const string& numStr1, int num2, int tailZero = 0) {
        if (num2 == 0) {
            return "0";
        }

        int carry = 0;
        stringstream ss;
        while (--tailZero >= 0) {
            ss << 0;
        }
        for (int i = 0, len1 = numStr1.length(); i < len1 || carry > 0; ++i) {
            int num1 = i < len1 ? numStr1[len1 - i - 1] - '0' : 0;
            int sum = num1 * num2 + carry;
            carry = sum / 10;
            ss << sum % 10;
        }
        auto res = ss.str();
        std::reverse(res.begin(), res.end());
        return res;
    }

    string plus(const string& numStr1, const string& numStr2) {
        if (numStr1 == "0") {
            return numStr2;
        }
        else if (numStr2 == "0") {
            return numStr1;
        }

        int len1 = numStr1.length();
        int len2 = numStr2.length();
        int maxLen = max(len1, len2);
        int carry = 0;
        stringstream ss;
        for (int i = 0; i < maxLen || carry > 0; ++i) {
            int num1 = i < len1 ? numStr1[len1 - i - 1] - '0' : 0;
            int num2 = i < len2 ? numStr2[len2 - i - 1] - '0' : 0;
            int sum = num1 + num2 + carry;
            carry = sum / 10;
            ss << sum % 10;
        }
        auto res = ss.str();
        std::reverse(res.begin(), res.end());
        return res;
    }




    bool isMatch_wildcardMatching(const string& s, const string& p) {
        auto sLen = int(s.length());
        auto pLen = int(p.length());
        if (sLen == 0) {
            return pLen == 0 || (pLen == 1 && p[0] == '*');
        }
        if (pLen == 0) {
            return sLen == 0;
        }

        auto pStart = p.front();
        if (pStart != '*' && pStart != '?' && pStart != s[0]) {
            return false;
        }
        auto pEnd = p.back();
        if (pEnd != '*' && pEnd != '?' && pEnd != s.back()) {
            return false;
        }

        vector<int> curValid {-1};
        for (int pIndex = 0; pIndex < pLen; ++pIndex) {
            auto pC = p[pIndex];
            vector<int> newValid {};
            if (pC == '*') {
                for (int i = curValid.front(); i < sLen; ++i) {
                    newValid.push_back(i);
                }
            }
            else {
                for (int i : curValid) {
                    if (i + 1 < sLen && (pC == '?' || pC == s[i + 1])) {
                        newValid.push_back(i + 1);
                    }
                }
            }

            if (newValid.empty()) {
                return false;
            }
            curValid = newValid;
        }
        return !curValid.empty() && curValid.back() == sLen - 1;
    }

    int indexOf(const string& s, const string& p) {
        if (s.length() < p.length()) {
            return false;
        }

        if (s.length() + p.length() == 0) {
            return true;
        }

        vector<int> next = kmpNext(p);
        int i = 0, j = 0, sLen = int(s.length()), pLen = int(p.length());
        for (; i < sLen && j < pLen;) {
            if (j == -1 || s[i] == p[j]) {
                i++;
                j++;
            }
            else {
                j = next[j];
            }
        }
        return j == pLen ? i - j : -1;
    }

    vector<int> kmpNext(const string& p) {
        vector<int> next {-1};
        for (int i = 0, j = -1, pLen = int(p.length()); i < pLen - 1;) {
            if (j == -1 || p[i] == p[j]) {
                next.push_back(++j);
                i++;
            }
            else {
                j = next[j];
            }
        }
        return next;
    }



    int jump(vector<int>& nums) {
        int size = int(nums.size());
        if (nums[0] + 1 >= size) {
            return min(1, size - 1);
        }

        int stepNum = 0;
        for (int i = 0; i < size - 1; ) {
            stepNum++;
            if (i + nums[i] >= size - 1) {
                return stepNum;
            }
            for (int j = i + 1, nextMax = j, last = i + nums[i]; j <= last; j++) {
                if (j + nums[j] >= nextMax) {
                    nextMax = j + nums[j];
                    i = j;
                }
            }
        }
        return stepNum;
    }


    /**
     * 不管是否有重复元素，都适用
     * @param nums
     * @return
     */
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res {};
        if (nums.size() <= 1) {
            res.push_back(nums);
            return res;
        }

        sort(nums.begin(), nums.end());
        res.push_back(nums);

        bool hasNext;
        do {
            hasNext = false;
            for (auto itI = nums.end() - 2, end = nums.begin() - 1; itI != end; itI--) {
                for (auto itJ = nums.end() - 1; itJ != itI; itJ--) {
                    if (*itI < *itJ) {
                        int temp = *itI;
                        *itI = *itJ;
                        *itJ = temp;
                        sort(itI + 1, nums.end());
                        res.push_back(nums);
                        hasNext = true;
                        goto permuteNext;
                    }
                }
            }
            permuteNext:;
        } while (hasNext);
        return res;
    }



    void rotate(vector<vector<int>>& matrix) {
        int n = int(matrix.size());
        if (n <= 1) {
            return;
        }

        for (int i = 0; i < n - 1 - i; i++) {
            for (int j = i; j < n - 1 - i; j++) {
                int leftTop = matrix[i][j];
                matrix[i][j] = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
                matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 -i];
                matrix[j][n - 1 -i] = leftTop;
            }
        }
    }



    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res {};
        int size = int(strs.size());
        if (size == 1) {
            res.push_back(strs);
        }
        else {
            unordered_map<string, int> hashIndexs {};
            for (auto &str : strs) {
                auto sorted = str;
                sort(sorted.begin(), sorted.end());
                auto f = hashIndexs.find(sorted);
                if (f != hashIndexs.end()) {
                    res[f->second].push_back(str);
                }
                else {
                    res.push_back({str});
                    hashIndexs[sorted] = int(res.size() - 1);
                }
            }
        }
        return res;
    }



    double myPow(double x, int n) {
        if (n < 0) {
            return 1.0 / myPow_(x, -n);
        }
        return myPow_(x, n);
    }

    double myPow_(double x, int n) {
        if (n == 0) {
            return 1;
        }

        double half = myPow_(x, n / 2);
        if (n % 2 == 0) {
            return half * half;
        }
        else {
            return half * half * x;
        }
    }


    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res = {};
        if (n == 1) {
            res.push_back(vector<string>{"Q"});
            return res;
        }
        else if (n <= 3) {
            return res;
        }

        vector<vector<char>> board(n, vector<char>(n, '.'));
        vector<bool> status(n * 6 - 2, true);
        for (int i = 0, half = n / 2; i < half; i++) {
            solveNQueens(board, status, 0, i, res);
        }

        int size = res.size();
        if (n % 2 == 1) {
            solveNQueens(board, status, 0, n / 2, res);
        }

        // 对称获取另一半结果
        for (int i = size - 1; i >= 0; --i) {
            auto& subRes = res[i];
            vector<string> reverseSubRes {};
            for (auto str : subRes) {
                reverseSubRes.emplace_back(str.rbegin(), str.rend());
            }
            res.push_back(reverseSubRes);
        }
        return res;
    }

    void solveNQueens(vector<vector<char>>& board, vector<bool>& status, int row, int col, vector<vector<string>>& res) {
        int size = board.size();
        if (isPosValid(status, size, row, col)) {
            board[row][col] = 'Q';
            if (row == size - 1) {
                addBoardToRes(board, res);
            }
            else {
                setPosStatus(status, size, row, col, false);
                for (int i = 0; i < size; i++) {
                    solveNQueens(board, status, row + 1, i, res);
                }
                setPosStatus(status, size, row, col, true);
            }
            board[row][col] = '.';
        }
    }

    void addBoardToRes(vector<vector<char>>& board, vector<vector<string>>& res) {
        vector<string> subRes {};
        for (auto boardRow : board) {
            subRes.emplace_back(boardRow.begin(), boardRow.end());
        }
        res.push_back(subRes);
    }

    bool isPosValid(vector<bool>& status, int size, int row, int col) {
        return status[row]
            && status[size + col]
            && status[size * 2 + (size - 1) - (row - col)]
            && status[size * 4 - 1 + (row + col)];
    }

    void setPosStatus(vector<bool>& status, int size, int row, int col, bool valid) {
        status[row] = valid;
        status[size + col] = valid;
        status[size * 2 + (size - 1) - (row - col)] = valid;
        status[size * 4 - 1 + (row + col)] = valid;
    }



    int totalNQueens(int n) {
        if (n == 1) {
            return 1;
        }
        else if (n <= 3) {
            return 0;
        }

        int res = 0;
        vector<vector<char>> board(n, vector<char>(n, '.'));
        vector<bool> status(n * 6 - 2, true);
        for (int i = 0, half = n / 2; i < half; i++) {
            res += totalNQueens(board, status, 0, i);
        }

        res *= 2;
        if (n % 2 == 1) {
            res += totalNQueens(board, status, 0, n / 2);
        }
        return res;
    }

    int totalNQueens(vector<vector<char>>& board, vector<bool>& status, int row, int col) {
        int res = 0;
        int size = board.size();
        if (isPosValid(status, size, row, col)) {
            board[row][col] = 'Q';
            if (row == size - 1) {
                res = 1;
            }
            else {
                setPosStatus(status, size, row, col, false);
                for (int i = 0; i < size; i++) {
                    res += totalNQueens(board, status, row + 1, i);
                }
                setPosStatus(status, size, row, col, true);
            }
            board[row][col] = '.';
        }
        return res;
    }


    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        int max = nums.front();
        int tempMax = max;
        for (int i = 1, size = int(nums.size()); i < size; i++) {
            int cur = nums[i];
            tempMax = std::max(tempMax + cur, cur);
            max = std::max(max, tempMax);
        }
        return max;
    }

    void test() {

//        {
//            vector<int> nums {-2,1,-3,4,-1,2,1,-5,4};
//            cout << maxSubArray(nums) << endl;
//        }


//        {
//            cout << totalNQueens(4) << endl;
//            cout << totalNQueens(5) << endl;
//        }

//        {
//            auto res = solveNQueens(5);
//            for (auto item : res) {
//                for (auto str : item) {
//                    cout << str << endl;
//                }
//                cout << endl;
//            }
//        }


//        {
//            cout << myPow(2.0, -10) << endl;
//        }


//        {
//            vector<string> strs {"has","rod","tom","hum","him","yon","met","dye"};
//            auto res = groupAnagrams(strs);
//            for (auto item : res) {
//                cout << item << endl;
//            }
//        }

//        {
//            vector<vector<int>> matrix = {
//                    {1, 2, 3},
//                    {4, 5, 6},
//                    {7, 8, 9}
//            };
//            for (auto item : matrix) {
//                cout << item << endl;
//            }
//            cout << endl;
//            rotate(matrix);
//            for (auto item : matrix) {
//                cout << item << endl;
//            }
//        }



//        {
//            vector<int> nums {6,3,2,7,4,-1};
//            auto res = permute(nums);
//            for (auto item : res) {
//                cout << item << endl;
//            }
//        }



//        {
//            vector<int> steps {2, 3, 1, 1, 4};
//            cout << jump(steps) << endl;
//            vector<int> steps1 {1, 2, 3};
//            cout << jump(steps1) << endl;
//            vector<int> steps2 {2,1,1,1,1};
//            cout << jump(steps2) << endl;
//            vector<int> steps3 {1,1,1,1};
//            cout << jump(steps3) << endl;
//            vector<int> steps4 {3,4,3,2,5,4,3};
//            cout << jump(steps4) << endl;
//        }


//        {
//            cout << kmpNext("abcabcdabcabcd") << endl;
//            cout << kmpNext("abcabd") << endl;
//            cout << indexOf("abcdabcb", "abcb") << endl;
//        }


//        {
//            cout << isMatch_wildcardMatching("aa", "a") << ' ' << 0 << endl;
//            cout << isMatch_wildcardMatching("aa", "*") << ' ' << 1 << endl;
//            cout << isMatch_wildcardMatching("cb", "?a") << ' ' << 0 << endl;
//            cout << isMatch_wildcardMatching("adceb", "*a*b") << ' ' << 1 << endl;
//            cout << isMatch_wildcardMatching("acdcb", "a*c?b") << ' ' << 0 << endl;
//        }


//        {
//            string res0 = multiply("123", "456");
//            cout << res0 << endl;
//
//            string res1 = multiply("9", "9");
//            cout << res1 << endl;
//        }



//        {
//            vector<int> height0 {0,1,0,2,1,0,1,3,2,1,2,1};
//            cout << trap(height0) << endl;
//
//            vector<int> height1 {2,1,0,2};
//            cout << trap(height1) << endl;
//
//            vector<int> height2 {4,2,0,3,2,5};
//            cout << trap(height2) << endl;
//        }



//        {
//            vector<int> nums {7,8,9,11,12};
//            int res = firstMissingPositive(nums);
//            cout << nums << endl;
//            cout << res << endl;
//        }


//        {
//            {
//                vector<int> candidates {10,1,2,7,6,1,5};
//                auto res = combinationSum2(candidates, 8);
//                for (auto item : res) {
//                    for (auto num : item) {
//                        cout << num << " ";
//                    }
//                    cout << "\n";
//                }
//                cout << endl;
//            }
//        }



//        {
//            {
//                vector<int> candidates {2, 3, 6, 7};
//                auto res = combinationSum(candidates, 7);
//                for (auto item : res) {
//                    for (auto num : item) {
//                        cout << num << " ";
//                    }
//                    cout << "\n";
//                }
//                cout << endl;
//            }
//            {
//                vector<int> candidates {7,3,2};
//                auto res = combinationSum(candidates, 18);
//                for (auto item : res) {
//                    for (auto num : item) {
//                        cout << num << " ";
//                    }
//                    cout << "\n";
//                }
//                cout << endl;
//            }
//        }


//        {
//            for (int i = 1; i <= 10; ++i) {
//                cout << countAndSay(i) << endl;
//            }
//        }


//        {
//            vector<vector<char>> board{};
//            buildSudokuVector(board, R"_(
//[
//  ["5","3",".",".","7",".",".",".","."],
//  ["6",".",".","1","9","5",".",".","."],
//  [".","9","8",".",".",".",".","6","."],
//  ["8",".",".",".","6",".",".",".","3"],
//  ["4",".",".","8",".","3",".",".","1"],
//  ["7",".",".",".","2",".",".",".","6"],
//  [".","6",".",".",".",".","2","8","."],
//  [".",".",".","4","1","9",".",".","5"],
//  [".",".",".",".","8",".",".","7","9"]
//]
//)_");
//            solveSudoku(board);
//            for (auto &item : board) {
//                for (auto c : item) {
//                    cout << c << "  ";
//                }
//                cout << '\n';
//            }
//            cout << endl;
//        }


//        {
//            vector<vector<char>> board {};
//            buildSudokuVector(board, R"_(
//[
//  ["5","3",".",".","7",".",".",".","."],
//  ["6",".",".","1","9","5",".",".","."],
//  [".","9","8",".",".",".",".","6","."],
//  ["8",".",".",".","6",".",".",".","3"],
//  ["4",".",".","8",".","3",".",".","1"],
//  ["7",".",".",".","2",".",".",".","6"],
//  [".","6",".",".",".",".","2","8","."],
//  [".",".",".","4","1","9",".",".","5"],
//  [".",".",".",".","8",".",".","7","9"]
//]
//)_");
//            cout << isValidSudoku(board) << endl;
//
//            buildSudokuVector(board, R"_(
//[
//[".",".",".",".","5",".",".","1","."],
//[".","4",".","3",".",".",".",".","."],
//[".",".",".",".",".","3",".",".","1"],
//["8",".",".",".",".",".",".","2","."],
//[".",".","2",".","7",".",".",".","."],
//[".","1","5",".",".",".",".",".","."],
//[".",".",".",".",".","2",".",".","."],
//[".","2",".","9",".",".",".",".","."],
//[".",".","4",".",".",".",".",".","."]
//]
//)_");
//            cout << isValidSudoku(board) << endl;
//        }


//        {
//            vector<int> nums {1,3,5,7};
//            int target = 6;
//            cout << searchInsert(nums, target) << endl;
//        }


//        {
//            vector<int> nums {5,7,7,8,8,10};
//            int target = 8;
//            cout << searchRange(nums, target) << endl;
//        }


//        {
//            {
//                vector<int> nums{4, 5, 6, 7, 0, 1, 2};
//                for (int i = 0; i < nums.size(); ++i) {
//                    cout << search(nums, nums[i}) << endl;
//                }
//            }
//        }


//        {
//            cout << longestValidParentheses("(((()()(()))") << endl;
//            cout << longestValidParentheses("()((())()") << endl;
//            cout << longestValidParentheses(")(((((()())()()))()(()))(") << endl;
//        }



//        {
//            vector<int> nums {1, 2, 3, 4, 5};
//            cout << nums << endl;
//            for (int i = 0; i < 25; ++i) {
//                nextPermutation(nums);
//                cout << nums << endl;
//            }
//        }


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


//        cout << isMatch_regexMatching("aa", "aa*a") << endl;
//        cout << isMatch_regexMatching("babcacacbbbacbaabbb", ".*.*b*ab*a*aa*b*.*c") << endl;
//        cout << isMatch_regexMatching("aa", "a") << endl;
//        cout << isMatch_regexMatching("aa", "a.") << endl;
//        cout << isMatch_regexMatching("aa", "a*") << endl;
//        cout << isMatch_regexMatching("ab", ".*") << endl;
//        cout << isMatch_regexMatching("", "a*") << endl;
//        cout << isMatch_regexMatching("", "") << endl;
//        cout << isMatch_regexMatching("", ".") << endl;
//        cout << isMatch_regexMatching("abcddde", "a.cd*e") << endl;


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
