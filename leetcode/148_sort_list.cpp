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
    ListNode* sortList(ListNode* head) {
        if (!head || !head -> next) return head;
        sort(head, NULL);
        
        return head;
    }
    
    void sort(ListNode* head, ListNode* tail) {
        if (head != tail && head -> next != tail) {
            ListNode* mid = partition(head, tail);
            sort(head, mid);
            sort(mid->next, tail);
        }  
    }
    
    ListNode* partition(ListNode* low, ListNode* high) {
        int key = low -> val;
        ListNode* loc = low;
        for (ListNode* i = low -> next; i != high; i = i -> next) {
            if (i -> val < key) {
                loc = loc -> next;
                swap(i -> val, loc -> val);
            }
        }
        
        swap(loc -> val, low -> val);
        return loc;
    }
};
