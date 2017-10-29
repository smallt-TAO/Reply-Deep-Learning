#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int fibonacci(int n) {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    vector<vector<int> > fibonacciSample(int n) {
        vector<vector<int> > temp;

        if (n == 1) {
            vector<int> te;
            te.push_back(1);
            temp.push_back(te);
            return temp;
        }

        if (n == 2) {
            vector<int> te1(2, 1);
            vector<int> te2(1, 2);
            temp.push_back(te1);
            temp.push_back(te2);
            return temp;
        }

        for (auto row : fibonacciSample(n - 1)) {
            vector<int> tm;
            for (auto col : row) {
                tm.push_back(col);
            }
            tm.push_back(1);
            temp.push_back(tm);
        }
        
        for (auto row : fibonacciSample(n - 2)) {
            vector<int> tm;
            for (auto col : row) {
                tm.push_back(col);
            }
            tm.push_back(2);
            temp.push_back(tm);
        }

        return temp;
    }
};

int main() {
    int n = 4;
    int res;
    Solution sol;
    res = sol.fibonacci(n);
    cout << res << endl;

    vector<vector<int> > re = sol.fibonacciSample(5);
    for (auto aa : re) {
        for(auto a : aa) {
            cout << a << " ";
        }
        cout << endl;
    }
}

