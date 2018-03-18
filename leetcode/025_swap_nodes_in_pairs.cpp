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
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head -> next) return head;
        ListNode* temp = head -> next;
        head -> next = swapPairs(head -> next -> next);
        temp -> next = head;
        
        return temp;
    }

        
};
