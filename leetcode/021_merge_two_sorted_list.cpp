/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* res = new ListNode(0);
        ListNode* dummy = res;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                res -> next = new ListNode(l1->val);
                res = res -> next;
                l1 = l1 -> next;
            }
            else {
                res -> next = new ListNode(l2->val);
                res = res -> next;
                l2 = l2 -> next;
            }
        }
        
        if (l1) res -> next = l1;
        if (l2) res -> next = l2;
        
        return dummy -> next;
        
    }
};
