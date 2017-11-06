#include <iostream>

using namespace std;

struct ListNode {
    int val;
    struct ListNode* next;
};


class Solution {
public:
    int findFirstCommonNode(ListNode* left, ListNode* right) {
        if (left == NULL || right == NULL) {
            return -1;
        }

        ListNode* leftHead = left;
        ListNode* rightHead = right;
        while (left != right) {
            left = left ? left -> next : rightHead;
            right = right ? right -> next : leftHead;
        }

        return left -> val;
    }
};


int main() {
    ListNode common[2];
    common[0].val = 6;
    common[0].next = &common[1];
    common[1].val = 7;
    common[1].next = NULL;

    ListNode left[3];
    left[0].val = 1;
    left[0].next = &left[1];
    left[1].val = 2;
    left[1].next = &left[2];
    left[2].val = 3;
    left[2].next = &common[0];

    ListNode right[2];
    right[0].val = 4;
    right[0].next = &right[1];
    right[1].val = 5;
    right[1].next = &common[0];

    Solution sol;
    cout << sol.findFirstCommonNode(left, right) << endl;

    return 0;
}

