#include <iostream>

using namespace std;

#define __tmain main
#ifdef __tmain 
#define debug cout
#else
#define debug 0 && cout
#endif

struct ListNode {
    int val;
    struct ListNode* next;
};

class Solution {
public:
    struct ListNode* mergeTwoList(ListNode* left, ListNode* right) {
        if (!left) {
            return right;
        }

        if (!right) {
            return left;
        }

        ListNode* merge = NULL;
        if (left -> val < right -> val) {
            merge = left;
            left = left -> next;
        }
        else {
            merge = right;
            right = right -> next;
        }

        ListNode* temp = merge;
        while ((left != NULL) && (right != NULL)) {
            debug << left -> val << "|" << right -> val << endl;

            if (left -> val < right -> val) {
                merge -> next = left;
                left = left -> next;
            }
            else {
                merge -> next = right;
                right = right -> next;
            }
            merge = merge -> next;
        }

        if (right) {
            merge -> next = right;
        }
        else {
            merge -> next = left;
        }

        return temp;
    }

    struct ListNode* mergeTwoList2(ListNode* left, ListNode* right) {
        if (!left) {
            debug << "finished the left";
            return right;
        }
        else if (!right) {
            debug << "finished the right";
            return left;
        }

        ListNode* head = NULL;

        if (left -> val < right -> val) {
            head = left;
            debug << head -> val << endl;
            head -> next = mergeTwoList2(left -> next, right);
        }
        else {
            head = right;
            debug << head -> val << endl;
            head -> next = mergeTwoList2(left, right -> next);
        }

        return head;
    }

};


int main() {
    ListNode left[2], right[3];

    left[0].val = 5;
    left[0].next = &left[1];
    left[1].val = 9;
    left[1].next = NULL;

    right[0].val = 1;
    right[0].next = &right[1];
    right[1].val = 2;
    right[1].next = &right[2];
    right[2].val = 4;
    right[2].next = NULL;


    Solution solu;
    ListNode* head = solu.mergeTwoList(left, right);
    while (head != NULL) {
        cout << head -> val;
        head = head -> next;
    }
    cout << endl;

    ListNode* res = solu.mergeTwoList2(left, right);
    while (res != NULL) {
        cout << res -> val;
        res = res -> next;
    }
    cout << endl;

    return 0;
}

