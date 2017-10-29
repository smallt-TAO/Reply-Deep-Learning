#include <iostream>

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
};

int main() {
    int n = 45;
    int res;
    Solution sol;
    res = sol.fibonacci(n);
    cout << res << endl;
}

