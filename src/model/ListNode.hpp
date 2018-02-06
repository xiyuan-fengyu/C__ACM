//
// Created by xiyuan_fengyu on 2018/1/10.
//

#ifndef C_ACM_LISTNODE_H
#define C_ACM_LISTNODE_H

#include <string>
#include <iostream>
#include <memory>
#include "util/util.hpp"

class ListNode {
public:
    int val;
    ListNode* next;

    explicit ListNode(int val): val(val), next(nullptr) {}

    static ListNode *parse(const std::string &str) {
        ListNode *head = nullptr;
        ListNode *cur = nullptr;
        std::stringstream ss;
        int value;
        auto splits = xiyuan::split(str, "->");
        for (auto &item : splits) {
            ss << item;
            ss >> value;
            ss.clear();
            auto newNode = new ListNode(value);
            if (head == nullptr) {
                head = cur = newNode;
            }
            else {
                cur->next = newNode;
                cur = newNode;
            }
        }
        return head;
    }

    friend std::ostream &operator<<(std::ostream &os, const ListNode &node) {
        os << node.val;
        if (node.next != nullptr) {
            ListNode* cur = node.next;
            while (cur != nullptr) {
                os << " -> " << cur->val;
                cur = cur->next;
            }
        }
        return os;
    }

//    virtual ~ListNode() {
//        std::cout << "ListNode@" << this << " release start" << std::endl;
//        if (next != nullptr) {
//            delete next;
//            next = nullptr;
//        }
//        std::cout << "ListNode@" << this << " release end" << std::endl;
//    }

};


#endif //C_ACM_LISTNODE_H
