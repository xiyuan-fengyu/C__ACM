//
// Created by xiyuan_fengyu on 2018/1/10.
//

#include <vector>
#include <string>
#include "ListNode.h"
#include "../util/util.h"

ListNode *ListNode::parse(const std::string &str) {
    ListNode* head = nullptr;
    ListNode* cur = nullptr;
    std::vector<std::string> splits = split(str, "->");
    std::stringstream ss;
    int value;
    for (const auto &item : splits) {
        ss.clear();
        ss << item;
        ss >> value;

        auto *newNode = new ListNode(value);
        if (head == nullptr) {
            cur = head = newNode;
        }
        else {
            cur->next = newNode;
            cur = newNode;
        }
    }
    return head;
}

std::ostream &operator<<(std::ostream &os, const ListNode &node) {
    os << node.val;
    if (node.next != nullptr) {
        ListNode* cur = node.next;
        while (cur != nullptr) {
            os << " <- " << cur->val;
            cur = cur->next;
        }
    }
    return os;
}
