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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (n < 1) return NULL;
        
        ListNode* root = new ListNode(0);
        root -> next = head;
        ListNode* temp = new ListNode(0);
        temp = root;
        
        for (int i = 0; i < n; i++) {
            if (head == NULL) return NULL;
            head = head -> next;
        }

        while (head) {
            temp = temp -> next;
            head = head -> next;
        }
        
        temp -> next = temp -> next -> next;
        
        return root -> next;
    }
};



