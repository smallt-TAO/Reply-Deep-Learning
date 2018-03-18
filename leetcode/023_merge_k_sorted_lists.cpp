/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct Pair {
    int val;
    int idx;
    Pair (int a, int b) {
        val = a;
        idx = b;
    }
};

struct ComPair { 
    bool operator() (Pair a, Pair b) {
        return a.val > b.val;
    }
};

class Solution {
    
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* dummy = new ListNode(0);
        ListNode* res = dummy;
        priority_queue<Pair, vector<Pair>, ComPair> pque;
        
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i]) {
                pque.push(Pair(lists[i] -> val, i));
                lists[i] = lists[i] -> next;
            }
        }
        
        while (!pque.empty()) {
            Pair temp = pque.top();
            dummy -> next = new ListNode(temp.val);
            dummy = dummy -> next;
            if (lists[temp.idx]) {
                pque.push(Pair(lists[temp.idx] -> val, temp.idx));
                lists[temp.idx] = lists[temp.idx] -> next;
            }
            pque.pop();
        }
        
        return res -> next;
    }
};
