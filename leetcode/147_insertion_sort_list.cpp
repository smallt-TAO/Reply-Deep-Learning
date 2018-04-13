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
    ListNode* insertionSortList(ListNode* head) {
        if (!head || !head->next) return head;
        
        ListNode* start = new ListNode(0);
        start -> next = head;
        ListNode* end = head;
        ListNode* p = head;
        
        while (p) {
            ListNode* temp = start -> next;
            ListNode* pre = start;
            while (temp != p && temp -> val < p -> val) {
                temp = temp -> next;
                pre = pre -> next;
            }
            if (temp == p) end = p;
            else {
                end -> next = p -> next;
                p -> next = temp;
                pre -> next = p;
            }
            p = end -> next;
        }
        
        return start -> next;
        
    }
};
