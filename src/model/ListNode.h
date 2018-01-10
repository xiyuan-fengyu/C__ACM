//
// Created by xiyuan_fengyu on 2018/1/10.
//

#ifndef C_ACM_LISTNODE_H
#define C_ACM_LISTNODE_H

#include <string>
#include <ostream>

class ListNode {
public:
    int val;
    ListNode* next;

    explicit ListNode(int val): val(val), next(nullptr) {}

    static ListNode* parse(const std::string& str);

    friend std::ostream &operator<<(std::ostream &os, const ListNode &node);

};


#endif //C_ACM_LISTNODE_H
