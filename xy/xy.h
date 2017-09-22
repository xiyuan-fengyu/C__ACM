//
// Created by xiyuan_fengyu on 2017/9/18.
//

#ifndef C_ACM_XY_H
#define C_ACM_XY_H

#include <iostream>
#include <vector>
#include <sstream>

namespace xy {

    using namespace std;

    //---- 字符串相关函数 start ----------------------------------------------------------------------------------------

    /**
     * 这个函数一定要在其他重载之前声明，否者会报类型推导失败的问题
     * @tparam T
     * @param begin
     * @param end
     * @param joinStr
     * @return
     */
    template <class T>
    static string join(T begin, T end, string joinStr) {
        ostringstream result;
        for (T it = begin; it != end; ++it) {
            if (it != begin) {
                result << joinStr;
            }
            result << *it;
        }
        return result.str();
    }

    template <class T>
    static string join(vector<T> vec, string joinStr) {
        return join(vec.begin(), vec.end(), joinStr);
    }

    template<class T, size_t N>
    static string join(array<T, N> arr, string joinStr) {
        return join(arr.begin(), arr.end(), joinStr);
    }

    template <class T>
    static string join(T begin, int offset, int length, string joinStr) {
        return join(begin + offset, begin + offset + length, joinStr);
    }

    template <class T>
    static string join(vector<T> vec, int offset, int length, string joinStr) {
        return join(vec.begin(), offset, length, joinStr);
    }

    template<class T, size_t N>
    static string join(array<T, N> arr, int offset, int length, string joinStr) {
        return join(arr.begin(), offset, length, joinStr);
    }

    template <class T>
    static string join(T begin, int length, string joinStr) {
        return join(begin, 0, length, joinStr);
    }

    static vector<string> split(string source, string divider) {
        vector<string> result;
        size_t last = 0;
        size_t index = source.find_first_of(divider, last);
        while (index != string::npos) {
            result.push_back(source.substr(last, index - last));
            last = index + 1;
            index = source.find_first_of(divider, last);
        }
        if (index - last > 0) {
            result.push_back(source.substr(last, index - last));
        }
        return result;
    }

    //---- 字符串相关函数 end ------------------------------------------------------------------------------------------





    //----    TreeNode 定义 start    -----------------------------------------------------------------------------------

    class TreeNode {
    public:
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int val) {
            this->val = val;
            this->left = this->right = nullptr;
        }
    };

    //----    TreeNode 定义 end    -------------------------------------------------------------------------------------


}

#endif //C_ACM_XY_H
