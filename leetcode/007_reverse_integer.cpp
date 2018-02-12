#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
    int reverse(int x) {
        bool neg = false;
        if (x < 0) {
            neg = true;
            x *= -1;
        }

        int res = x % 10;
        x /= 10;
        while (x) {
            res = res * 10 + x % 10;
            x /= 10;
        }

        return res * (neg ? -1 : 1);
    }
};

int main() {
    Solution sol;
    cout << sol.reverse(89) << endl;
    cout << sol.reverse(-89) << endl;
    cout << sol.reverse(8900) << endl;

    return 0;
}

