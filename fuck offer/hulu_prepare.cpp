#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Pair {
    int ai;
    int bj;
    int val;
    Pair() {
        ai = bj = val = 0;
    }

    Pair(int i, int j, int val) {
        ai = i;
        bj = j;
        this->val = val;
    }
};

struct ComPair {
    bool operator() (Pair a, Pair b) {
        return a.val > b.val;
    }
};

vector<int> minKSum(vector<int>& A, vector<int>& B, int K) {
    int n = A.size();
    int k = 0;
    int i = 0;
    int j = 0;
    priority_queue<Pair, vector<Pair>, ComPair> pque;
    pque.push(Pair(0, 0, A[0] + B[0]));
    
    vector<int> res;
    while (k < K && !pque.empty()) {
        Pair p = pque.top();
        res.push_back(p.val);
        ++k;
        pque.pop();
        
        pque.push(Pair(p.ai + 1, p.bj, A[p.ai + 1] + B[p.bj]));
        pque.push(Pair(p.ai, p.bj + 1, A[p.ai] + B[p.bj + 1]));
    }

    return res;
}


int main() {
    int  A[] = {10, 11, 12, 13, 17, 30};  
    vector<int> vecA(A, A + 6);  
    int B[] = {-5, -2, 0, 9, 10, 43};  
    vector<int> vecB(B, B + 6);
    
    for (auto i : minKSum(vecA, vecB, 5)) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

     

