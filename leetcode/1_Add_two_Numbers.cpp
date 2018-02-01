// leetcode 2
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <vector>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* res = new ListNode(0);
        ListNode* ss = res;
        int temp = 0;
        while (l1 || l2 || temp) {
            int l1Sum = l1 ? l1 -> val : 0;
            int l2Sum = l2 ? l2 -> val : 0;
            int sum = l1Sum + l2Sum + temp;
            ss -> next = new ListNode(sum % 10);
            temp = sum / 10;
            ss = ss -> next;
            l1 = l1 ? l1 -> next : l1;
            l2 = l2 ? l2 -> next : l2;
        }
        return res -> next;
    }
};

int main() {
    ListNode* one = new ListNode(2);
    ListNode* two = new ListNode(3);

    Solution sol;
    ListNode* res = sol.addTwoNumbers(one, two);
    while(res != NULL) {
        cout << res->val << endl;
        res = res -> next;
    }

    return 1;
}

