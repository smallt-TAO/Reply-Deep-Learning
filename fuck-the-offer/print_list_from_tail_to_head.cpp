#include <iostream>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    struct ListNode* next;
    // ListNode(int x):val(x), next(NULL) {}
};

class Solution {
    public:
    void printListFromTailToHead(struct ListNode* head) {
        if (head) {
            printListFromTailToHead(head->next);
            cout << head->val << " ";
        }
    }

    void printListFromTailToHeadWithStack(struct ListNode* head) {
        stack<int> res;
        while (head) {
            res.push(head->val);
            // cout << head->val << " ";
            head = head->next;
        }

        while (!res.empty()) {
            cout << res.top() << " ";
            res.pop();
        }
    }

};


int main() {
    ListNode head[4];
    head[0].val = 1;
    head[0].next = &head[1];
    head[1].val = 2;
    head[1].next = &head[2];
    head[2].val = 3;
    head[2].next = NULL;

    Solution sol;
    sol.printListFromTailToHead(head);
    cout << endl;
    sol.printListFromTailToHeadWithStack(head);
    cout << endl;

    return 0;
}
