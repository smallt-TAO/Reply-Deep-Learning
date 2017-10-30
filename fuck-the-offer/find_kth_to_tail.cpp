#include <iostream>

using namespace std;

struct ListNode {
    int val;
    struct ListNode* next;
};

class Solution {
    public:
    void findKthToTail(struct ListNode* root, int k) {
        ListNode* left = root;
        ListNode* right = root;

        while (k) {
            right = right->next;
            k--;
        }

        while (right) {
            right = right -> next;
            left = left -> next;
        }

        cout << left -> val << endl;
    }
};

int main() {
    ListNode List[3];
    List[0].val = 1;
    List[0].next = &List[1];
    List[1].val = 2;
    List[1].next = &List[2];
    List[2].val = 3;
    List[2].next = NULL;

    Solution sol;
    sol.findKthToTail(List, 1);
    sol.findKthToTail(List, 2);

    return 0;
}

