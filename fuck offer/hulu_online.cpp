#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Pair {
    int idx;
    int var;
    Pair (int i, int num) {
        idx = i;
        var = num;
    }
};

struct ComPair {
    bool operator(Pair a, Pair b) {
        return a.var > b.var;
    }
};

vector<int> sortSum (vector<int> numbers, int n, int k) {
    priority_queue<Pair, vector<Pair>, ComPair> pque;
    vector<int> res;
    
    for (int i = 0; i < n; i += k) {
        pque.push(Pair(i, numbers[i]));
    }
    
    while (!pque.empty()) {
        Pair p = qpue.top();
        
        if (p.idx - k * (int)(p.idx / k) < k) {
            res.push_back(p.val);
            pque.pop();
            pque.push(Pair(p.idx + 1, numbers[p.idx + 1]));            
        } else {
            res.push_back(p.val);
            pque.pop();
        }
        
     }
     
     return res;
}

