#include <iostream>

using namespace std;

struct ListNode {
    int val;
    struct ListNode* next;
};

class Solution {
    public:
    ListNode* reverseList(struct ListNode* root) {
        ListNode* temp = NULL;

        while (root != NULL) {
            ListNode* next = root -> next;
            root -> next = temp;

            temp = root;
            root = next;
        }

        return temp;
    }

    ListNode* reverse(struct ListNode* head) {
        if (head == NULL || head -> next == NULL) {
            return head;
        }

        ListNode* pre = reverse(head -> next);
        head -> next -> next = head;
        head -> next = NULL;

        return pre;
    }
};

int main() {
    ListNode list[4];
    list[0].val = 1;
    list[0].next = &list[1];
    list[1].val = 2;
    list[1].next = &list[2];
    list[2].val = 3; 
    list[2].next = &list[3];
    list[3].val = 4;
    list[3].next = NULL;

    ListNode* node = list;
    while(node != NULL) {
        cout << node -> val;
        node = node -> next;
    }
    cout << endl;

    Solution sol;
    node = sol.reverseList(list);

    ListNode* list1 = node;
    while (node) {
        cout << node -> val;
        node = node -> next;
    }
    cout << endl;

    node = sol.reverse(list1);
    while (node) {
        cout << node -> val;
        node = node -> next;
    }
    cout << endl;
    return 0;
    
}
