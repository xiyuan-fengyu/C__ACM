//
// Created by xiyuan_fengyu on 2018/2/8.
//

#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {

    unordered_map<string, int> m;
    m["test"] = 2;
    m.find("test")->second++;
    cout << m["test"] << endl;

    m["other"]++;
    cout << m["other"] << endl;

    return 0;
}